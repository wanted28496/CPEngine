#include"FSA.h"
#include"BitArray.h"
#include"HeapManager.h"
#include"Console.h"


static unsigned char _bNoMansLandFill = 0xFD; /* fill no-man's land with this */
static unsigned char _bAlignLandFill = 0xED; /* fill no-man's land for aligned routines */
static unsigned char _bDeadLandFill = 0xDD; /* fill free objects with this */
static unsigned char _bCleanLandFill = 0xCD; /* fill new objects with this */


FixedSizedAllocator::FixedSizedAllocator() {

}

FixedSizedAllocator::FixedSizedAllocator(size_t i_blockSize, size_t i_numBlocks, HeapManager* i_heap):
	m_blockSize(i_blockSize)
{
	if (i_numBlocks % 8 != 0) {
		m_numBlocks = i_numBlocks + (8 - (i_numBlocks % 8));
	}
	else {
		m_numBlocks = i_numBlocks;
	}
	m_bitArray = BitArray::createBitArray(m_numBlocks, i_heap);
	m_startingAddress = i_heap->alloc(m_numBlocks * i_blockSize);
}

FixedSizedAllocator::~FixedSizedAllocator() {

}


#if _DEBUG
void * FixedSizedAllocator::alloc(size_t i_size) {
	size_t availableBlock;
	if (m_bitArray->GetFirstSetBit(availableBlock)) {

		m_bitArray->ClearBit(availableBlock);

		char* addresses = reinterpret_cast<char*>(m_startingAddress) + (availableBlock * m_blockSize);
		char* tempAddress = reinterpret_cast<char*>(m_startingAddress) + (availableBlock * m_blockSize);

		size_t remaining = m_blockSize - i_size;
		
		//Filling the memory with LandFills 
		while (tempAddress < addresses + 4) {
			*tempAddress = _bNoMansLandFill;
			tempAddress++;
		}
		char* returnAddress = tempAddress;
		while (tempAddress < addresses + i_size - 4) {
			*tempAddress = _bCleanLandFill;
			tempAddress++;
		}
		while (tempAddress < addresses + i_size + remaining - 4) {
			*tempAddress = _bAlignLandFill;
			tempAddress++;
		}
		while (tempAddress < addresses + i_size + remaining) {
			*tempAddress = _bNoMansLandFill;
			tempAddress++;
		}
		return returnAddress;
	}
	else {
		return nullptr;
	}
}

bool FixedSizedAllocator::freeMemory(void * i_block) {
	size_t freedBit = (reinterpret_cast<char*>(i_block) - m_startingAddress) / m_blockSize;

	m_bitArray->setBit(freedBit);
	char* address = reinterpret_cast<char*>(i_block) - 4;
	while (address < reinterpret_cast<char*>(i_block) + m_blockSize - 4) {
		*address = _bDeadLandFill;
		address++;
	}
	return true;
}
#else
void * FixedSizedAllocator::alloc(size_t i_size) {
	size_t availableBlock;
	if (m_bitArray->GetFirstSetBit(availableBlock)) {

		m_bitArray->ClearBit(availableBlock);
		char* addresses = reinterpret_cast<char*>(m_startingAddress) + (availableBlock * m_blockSize);
		char* tempAddress = reinterpret_cast<char*>(m_startingAddress) + (availableBlock * m_blockSize);

		//Filling the memory with LandFills 
		char* returnAddress = tempAddress;
		while (tempAddress < addresses + i_size) {
			*tempAddress = _bCleanLandFill;
			tempAddress++;
		}
		return addresses;
	}
	return nullptr;
}

bool FixedSizedAllocator::freeMemory(void * i_block) {
	size_t freedBit = (reinterpret_cast<char*>(i_block) - m_startingAddress) / m_blockSize;
	m_bitArray->setBit(freedBit);
	char* address = reinterpret_cast<char*>(i_block);
	while (address < reinterpret_cast<char*>(i_block) + m_blockSize) {
		*address = _bDeadLandFill;
		address++;
	}
	return true;
}
#endif

void FixedSizedAllocator::destroy(HeapManager* i_heap) {
	size_t index;
	if (!m_bitArray->GetFirstClearBit(index)) {
		i_heap->freeMemory(m_startingAddress);
		m_startingAddress = nullptr;

		m_bitArray->Destroy(i_heap);
		i_heap->freeMemory(m_bitArray);
		m_bitArray = nullptr;
	}
	else {
		// Outstadning Allocations
		/*while (m_bitArray->GetFirstClearBit(index)) {
			DEBUG_PRINT("Outstanding Allocations");
			void* block = reinterpret_cast<char*>(m_startingAddress) + (index * m_blockSize);
			freeMemory(block);
		}

		i_heap->freeMemory(m_startingAddress);
		m_startingAddress = nullptr;

		m_bitArray->Destroy(i_heap);
		i_heap->freeMemory(m_bitArray);
		m_bitArray = nullptr;*/

	}
}
/**
BitArray.cpp
purpose: Creating a bit array for Fixed Size Allocator
@author Mit Doshi
@version 1.1 12/16/2018
*/

#include<iostream>
#include<conio.h>
#include<intrin.h>
#include"BitArray.h"
#include"HeapManager.h"


BitArray::BitArray() {
	
}

/**
	Destructor of Bit Array object
*/
BitArray::~BitArray() {
	if (m_bits) {
		delete m_bits;
	}
}

/**
	Creates the Bit Array and allocates memory needed for maintaining the Blocks of Fixed Size Allocator

	@params i_numbits a size_t variable containing the number of blocks of Fixed Size Allocator
	@params i_Allocator a Heapmanager pointer to allocate memory from heap manager
	@params i_initToZero a boolean to set all the bits to zero on allocation, default false
	@return a pointer of bit array class
*/
BitArray * BitArray::createBitArray(size_t i_numbits, HeapManager* i_Allocator, bool i_initToZero) {
	
	BitArray* bitArray = reinterpret_cast<BitArray*>(i_Allocator->alloc(sizeof(BitArray*)));
	const size_t bitPerItem = 8;
	bitArray->m_size = ceil(i_numbits / bitPerItem);
	//memset(bitArray->m_bits, i_initToZero ? 0 : 1, size);
	bitArray->m_bits = reinterpret_cast<unsigned char*>(i_Allocator->alloc(bitArray->m_size));

	for (unsigned int i = 0; i < bitArray->m_size; i++) {
		for (unsigned int j = 0; j < bitPerItem; j++) {
			bitArray->m_bits[i] |= 1ULL << j;
		}
	}

	return bitArray;
}


/**
	set all the bits to 0
*/
void BitArray::ClearAll(void) const {
	//memset(m_bits, 0, sizeof(m_bits));
	const size_t bitPerItem = 8;

	for (unsigned int i = 0; i < m_size; i++) {
		for (unsigned int j = 0; j < bitPerItem; j++) {
			m_bits[i] &= ~(1ULL << j);
		}
	}
}

/**
	sets all the bits to 1
*/
void BitArray::SetAll(void) const {
	//memset(m_bits, 1, sizeof(m_bits));

	const size_t bitPerItem = 8;
	
	for (unsigned int i = 0; i < m_size; i++) {
		for (unsigned int j = 0; j < bitPerItem; j++) {
			m_bits[i] |= 1ULL << j;
		}
	}
}

/**
	checks weather the bit is 1 or not

	@params i_bitNumber a size_t value for the bit to check
	@return a boolean weather the bit is 1 or not
*/
inline bool BitArray::IsBitSet(size_t i_bitNumber) const {
	const size_t bitPerItem = 8;

	size_t index = i_bitNumber / bitPerItem;
	size_t number = i_bitNumber % bitPerItem;
	return (m_bits[index] >> number) & 1ULL;
}

/**
checks weather the bit is 0 or not

@params i_bitNumber a size_t value for the bit to check
@return a boolean weather the bit is 0 or not
*/
inline bool BitArray::IsBitClear(size_t i_bitNumber) const {

	const size_t bitPerItem = 8;
	size_t index = i_bitNumber / bitPerItem;
	size_t number = i_bitNumber % bitPerItem;
	return !((m_bits[index] >> number) & 1ULL);
}

/**
set the bit to 1 at the specified location

@params i_bitNumber a size_t value for the bit location
*/
void BitArray::setBit(size_t i_bitNUmber) const {
	
	const size_t bitPerItem = 8;
	size_t index = i_bitNUmber / bitPerItem;
	size_t number = i_bitNUmber % bitPerItem;
	m_bits[index] |= 1ULL << number;
}

/**
set the bit to 0 at the specified location

@params i_bitNumber a size_t value for the bit location
*/
void BitArray::ClearBit(size_t i_bitNUmber) const {
	const size_t bitPerItem = 8;
	size_t index = i_bitNUmber / bitPerItem;
	size_t number = i_bitNUmber % bitPerItem;
	m_bits[index] &= ~(1ULL << number);
}

/**
gets the first bit which is 0 in the bit array

@params o_bitNumber a size_t out variable which stores the bit location
@return a bool value weather there is 0 bit in the bit array
*/

bool BitArray::GetFirstClearBit(size_t & o_bitNUmber) const {
	const size_t bitPerItem = 8;
	unsigned long index;
	unsigned char negate;
	bool bitfound = false;
	for (unsigned int i = 0; i < m_size; i++) {
		negate = ~m_bits[i];
#if _WIN64
		if (_BitScanReverse64(&index, negate)) {
			bitfound = true;
			o_bitNUmber = i * bitPerItem + index;
			break;
		}
#else
		if (_BitScanReverse(&index, negate)) {
			bitfound = true;
			o_bitNUmber = i * bitPerItem + index;
			break;
		}
#endif
	}
	return bitfound;

}

/**
gets the first bit which is 1 in the bit array

@params o_bitNumber a size_t out variable which stores the bit location
@return a bool value weather there is 1 bit in the bit array
*/
bool BitArray::GetFirstSetBit(size_t & o_bitNUmber) const {
	
	const size_t bitPerItem = 8;
	unsigned long index;
	bool bitfound = false;

	for (unsigned int i = 0; i < m_size; i++) {
#if _WIN64
		if (_BitScanReverse64(&index, m_bits[i])) {
			bitfound = true;
			o_bitNUmber = i * bitPerItem + index;
			break;
		}
#else
		if (_BitScanReverse(&index, m_bits[i])) {
			bitfound = true;
			o_bitNUmber = i * bitPerItem + index;
			break;
		}
#endif
	}
	return bitfound;
}

/**
	Destroys the Bit array class and frees the memory

	@params i_heap HeapManager instance to free memory from
*/
void BitArray::Destroy(HeapManager* i_heap) {
	i_heap->freeMemory(m_bits);
	m_bits = nullptr;
}
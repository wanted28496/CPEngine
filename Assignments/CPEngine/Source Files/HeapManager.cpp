/**
 HeapManager.cpp
 purpose: custom memory Management
 @author Mit Doshi
 @version 1.4 12/2/2018
*/

#include<iostream>
#include"HeapManager.h"
#include"Console.h"
using namespace std;
using namespace Engine;


static unsigned char _bNoMansLandFill = 0xFD; /* fill no-man's land with this */
static unsigned char _bAlignLandFill = 0xED; /* fill no-man's land for aligned routines */
static unsigned char _bDeadLandFill = 0xDD; /* fill free objects with this */
static unsigned char _bCleanLandFill = 0xCD; /* fill new objects with this */


//HeapManager::HeapManager() {
//	_instance = this;
//}
//HeapManager::HeapManager(void * i_memoryBlock, size_t i_size, unsigned int i_descriptor) {
//	m_head = i_memoryBlock;
//	m_heapSize = i_size;
//	m_numDescriptor = i_descriptor;
//	_instance = this;
//}
//HeapManager::~HeapManager() {
//	m_allocatedBlockHead = nullptr;
//	m_freeBlockHead = nullptr;
//	m_blockDiscriptorMaintainer = nullptr;
//	m_head = nullptr;
//	m_heapSize = NULL;
//	m_numDescriptor = NULL;
//	_instance = nullptr;
//}
HeapManager* HeapManager::operator=(HeapManager* i_rhs) {
	this->m_allocatedBlockHead = i_rhs->m_allocatedBlockHead;
	this->m_freeBlockHead = i_rhs->m_freeBlockHead;
	this->m_blockDiscriptorMaintainer = i_rhs->m_blockDiscriptorMaintainer;

	this->m_head = i_rhs->m_head;
	this->m_heapSize = i_rhs->m_heapSize;
	this->m_numDescriptor = i_rhs->m_numDescriptor;
	return this;
}

HeapManager * HeapManager::createHeap(void * i_memoryBlock, size_t i_size, unsigned int i_descriptor) {
	HeapManager* heap = reinterpret_cast<HeapManager*>(reinterpret_cast<char*>(i_memoryBlock) + i_size - i_descriptor * sizeof(BlockDescriptor) - sizeof(HeapManager));

	heap->m_head = i_memoryBlock;
	heap->m_heapSize = i_size;
	heap->m_numDescriptor = i_descriptor;

	heap->m_freeBlockHead = reinterpret_cast<BlockDescriptor*>(reinterpret_cast<char *>(i_memoryBlock) + i_size - i_descriptor * sizeof(BlockDescriptor));
	heap->m_freeBlockHead->m_size = i_size - i_descriptor * sizeof(BlockDescriptor) - sizeof(HeapManager);
	heap->m_freeBlockHead->m_startAddr = i_memoryBlock;
	heap->m_freeBlockHead->m_next = nullptr;

	heap->m_allocatedBlockHead = nullptr;
	heap->m_blockDiscriptorMaintainer = heap->m_freeBlockHead + sizeof(BlockDescriptor);

	BlockDescriptor * temp = heap->m_blockDiscriptorMaintainer;
	unsigned int count = 0;
	while (count < i_descriptor) {
		count++;
		temp->m_size = 0;
		temp->m_startAddr = nullptr;
		temp->m_next = reinterpret_cast<BlockDescriptor*>(reinterpret_cast<char*>(temp) + sizeof(BlockDescriptor));
		temp = reinterpret_cast<BlockDescriptor*>(temp->m_next);
	}
	temp->m_next = nullptr;

	return heap;
}

void HeapManager::destroy() {
	m_head = nullptr;
	m_heapSize = NULL;
	m_numDescriptor = NULL;
	count = NULL;

	m_allocatedBlockHead = nullptr;
	m_freeBlockHead = nullptr;
	m_blockDiscriptorMaintainer = nullptr;
}



#if defined(_DEBUG)
	void * HeapManager::alloc(size_t i_size) {
		BlockDescriptor* freeBlocks = m_freeBlockHead;
		BlockDescriptor* toBeAllocated = m_blockDiscriptorMaintainer;
		do {
			if (freeBlocks->m_size >= i_size + 8) {
				if (m_blockDiscriptorMaintainer->m_next != nullptr) {
					m_blockDiscriptorMaintainer = reinterpret_cast<BlockDescriptor*>(m_blockDiscriptorMaintainer->m_next);
					toBeAllocated->m_startAddr = freeBlocks->m_startAddr;
					toBeAllocated->m_size = i_size + 8;
					freeBlocks->m_size = freeBlocks->m_size - i_size - 8;
					freeBlocks->m_startAddr = reinterpret_cast<void*>(reinterpret_cast<char*>(freeBlocks->m_startAddr) + i_size + 8);

					if (m_allocatedBlockHead == nullptr) {
						m_allocatedBlockHead = toBeAllocated;
						m_allocatedBlockHead->m_next = nullptr;
						char* addresses = reinterpret_cast<char*>(toBeAllocated->m_startAddr);
						while (addresses < reinterpret_cast<char*>(toBeAllocated->m_startAddr) + 4) {
							*addresses = _bNoMansLandFill;
							addresses++;
						}
						void* returnedAddress = addresses;
						while (addresses < reinterpret_cast<char*>(toBeAllocated->m_startAddr) + i_size + 4) {
							*addresses = _bCleanLandFill;
							addresses++;
						}
						while (addresses < reinterpret_cast<char*>(toBeAllocated->m_startAddr) + i_size + 8) {
							*addresses = _bNoMansLandFill;
							addresses++;
						}
						return returnedAddress;
					}
					else {
						BlockDescriptor* mainBlock = m_allocatedBlockHead;
						while (mainBlock->m_next != nullptr) {
							mainBlock = reinterpret_cast<BlockDescriptor*>(mainBlock->m_next);
						}
						toBeAllocated->m_next = nullptr;
						mainBlock->m_next = toBeAllocated;
						char* addresses = reinterpret_cast<char*>(toBeAllocated->m_startAddr);
						while (addresses < reinterpret_cast<char*>(toBeAllocated->m_startAddr) + 4) {
							*addresses = _bNoMansLandFill;
							addresses++;
						}
						void* returnedAddress = addresses;
						while (addresses < reinterpret_cast<char*>(toBeAllocated->m_startAddr) + i_size + 4) {
							*addresses = _bCleanLandFill;
							addresses++;
						}
						while (addresses < reinterpret_cast<char*>(toBeAllocated->m_startAddr) + i_size + 8) {
							*addresses = _bNoMansLandFill;
							addresses++;
						}
					return returnedAddress;
					}
				}
				else {
					return nullptr;
				}
			}
			freeBlocks = reinterpret_cast<BlockDescriptor*>(freeBlocks->m_next);
		} while (freeBlocks != nullptr);
		return nullptr;
	}

	void * HeapManager::alloc(size_t i_size, unsigned int i_allign) {
		unsigned int paddingNeeded = (i_size + 8) % i_allign;
		BlockDescriptor* freeBlocks = m_freeBlockHead;
		BlockDescriptor* toBeAllocated = m_blockDiscriptorMaintainer;
		do {
			if (freeBlocks->m_size >= i_size + 8 + paddingNeeded) {
				if (m_blockDiscriptorMaintainer->m_next != nullptr) {
					m_blockDiscriptorMaintainer = reinterpret_cast<BlockDescriptor*>(m_blockDiscriptorMaintainer->m_next);
					toBeAllocated->m_startAddr = freeBlocks->m_startAddr;
					toBeAllocated->m_size = i_size + 8 + paddingNeeded;
					freeBlocks->m_size = freeBlocks->m_size - i_size - 8 - paddingNeeded;
					freeBlocks->m_startAddr = reinterpret_cast<void*>(reinterpret_cast<char*>(freeBlocks->m_startAddr) + i_size + 8 + paddingNeeded);
					// No allocations in the descriptor
					if (m_allocatedBlockHead == nullptr) {
						m_allocatedBlockHead = toBeAllocated;
						m_allocatedBlockHead->m_next = nullptr;
						char* addresses = reinterpret_cast<char*>(toBeAllocated->m_startAddr);
						// four while loops to add padding and Gaurdbands at the location
						while (addresses < reinterpret_cast<char*>(freeBlocks->m_startAddr) + 4) {
							*addresses = _bNoMansLandFill;
							addresses++;
						}
						void* returnedAddress = addresses;
						while (addresses < reinterpret_cast<char*>(freeBlocks->m_startAddr) + i_size + 4) {
							*addresses = _bCleanLandFill;
							addresses++;
						}
						while (addresses < reinterpret_cast<char*>(freeBlocks->m_startAddr) + i_size + 4 + paddingNeeded) {
							*addresses = _bAlignLandFill;
							addresses++;
						}
						while (addresses < reinterpret_cast<char*>(freeBlocks->m_startAddr) + i_size + 8 + paddingNeeded) {
							*addresses = _bNoMansLandFill;
							addresses++;
						}
						return returnedAddress;
					}
					else {//There is some Allocations
						BlockDescriptor* mainBlock = m_allocatedBlockHead;
						while (mainBlock->m_next != nullptr) {
							mainBlock = reinterpret_cast<BlockDescriptor*>(mainBlock->m_next);
						}
						toBeAllocated->m_next = nullptr;
						mainBlock->m_next = toBeAllocated;
						char* addresses = reinterpret_cast<char*>(toBeAllocated->m_startAddr);
						//four while loops to add padding and gaurdband at the memory location
						while (addresses < reinterpret_cast<char*>(freeBlocks->m_startAddr) + 4) {
							*addresses = _bNoMansLandFill;
							addresses++;
						}
						void* returnedAddress = addresses;
						while (addresses < reinterpret_cast<char*>(freeBlocks->m_startAddr) + i_size + 4) {
							*addresses = _bCleanLandFill;
							addresses++;
						}
						while (addresses < reinterpret_cast<char*>(freeBlocks->m_startAddr) + i_size + 4 + paddingNeeded) {
							*addresses = _bAlignLandFill;
							addresses++;
						}
						while (addresses < reinterpret_cast<char*>(freeBlocks->m_startAddr) + i_size + 8 + paddingNeeded) {
							*addresses = _bNoMansLandFill;
							addresses++;
						}
						return returnedAddress;
					}
				}
				else {
					return nullptr;
				}
			}
			freeBlocks = reinterpret_cast<BlockDescriptor*>(freeBlocks->m_next);
		} while (m_freeBlockHead != nullptr);
		return nullptr;
	}

#else
void * HeapManager::alloc(size_t i_size) {
	BlockDescriptor* freeBlocks = m_freeBlockHead;
	BlockDescriptor* toBeAllocated = m_blockDiscriptorMaintainer;
	do {
		if (freeBlocks->m_size >= i_size) {
			if (m_blockDiscriptorMaintainer->m_next != nullptr) {
				m_blockDiscriptorMaintainer = reinterpret_cast<BlockDescriptor*>(m_blockDiscriptorMaintainer->m_next);
				toBeAllocated->m_startAddr = freeBlocks->m_startAddr;
				toBeAllocated->m_size = i_size;
				freeBlocks->m_size = freeBlocks->m_size - i_size;
				freeBlocks->m_startAddr = reinterpret_cast<void*>(reinterpret_cast<char*>(freeBlocks->m_startAddr) + i_size);

				if (m_allocatedBlockHead == nullptr) {
					m_allocatedBlockHead = toBeAllocated;
					m_allocatedBlockHead->m_next = nullptr;
					char* addresses = reinterpret_cast<char*>(toBeAllocated->m_startAddr);
					void* returnedAddress = addresses;
					while (addresses < reinterpret_cast<char*>(toBeAllocated->m_startAddr) + i_size) {
						*addresses = _bCleanLandFill;
						addresses++;
					}
					return returnedAddress;
				}
				else {
					BlockDescriptor* mainBlock = m_allocatedBlockHead;
					while (mainBlock->m_next != nullptr) {
						mainBlock = reinterpret_cast<BlockDescriptor*>(mainBlock->m_next);
					}
					toBeAllocated->m_next = nullptr;
					mainBlock->m_next = toBeAllocated;
					char* addresses = reinterpret_cast<char*>(toBeAllocated->m_startAddr);
					void* returnedAddress = addresses;
					while (addresses < reinterpret_cast<char*>(toBeAllocated->m_startAddr) + i_size) {
						*addresses = _bCleanLandFill;
						addresses++;
					}
					return returnedAddress;
				}
			}
			else {
				return nullptr;
			}
		}
		freeBlocks = reinterpret_cast<BlockDescriptor*>(freeBlocks->m_next);
	} while (freeBlocks != nullptr);
	return nullptr;
}

void * HeapManager::alloc(size_t i_size, unsigned int i_allign) {
	unsigned int paddingNeeded = i_size % i_allign;
	BlockDescriptor* freeBlocks = m_freeBlockHead;
	BlockDescriptor* toBeAllocated = m_blockDiscriptorMaintainer;
	do {
		if (freeBlocks->m_size >= i_size + paddingNeeded) {
			if (m_blockDiscriptorMaintainer->m_next != nullptr) {
				m_blockDiscriptorMaintainer = reinterpret_cast<BlockDescriptor*>(m_blockDiscriptorMaintainer->m_next);
				toBeAllocated->m_startAddr = freeBlocks->m_startAddr;
				toBeAllocated->m_size = i_size + paddingNeeded;
				freeBlocks->m_size = freeBlocks->m_size - i_size - paddingNeeded;
				freeBlocks->m_startAddr = (void*)((intptr_t)freeBlocks->m_startAddr + i_size + paddingNeeded);
				// No allocations in the descriptor
				if (m_allocatedBlockHead == nullptr) {
					m_allocatedBlockHead = toBeAllocated;
					m_allocatedBlockHead->m_next = nullptr;
					char* addresses = reinterpret_cast<char*>(toBeAllocated->m_startAddr);
					// four while loops to add padding and Gaurdbands at the location
					while (addresses < reinterpret_cast<char*>(freeBlocks->m_startAddr) + i_size) {
						*addresses = _bNoMansLandFill;
						addresses++;
					}
					while (addresses < reinterpret_cast<char*>(freeBlocks->m_startAddr) + i_size + paddingNeeded) {
						*addresses = _bAlignLandFill;
						addresses++;
					}
					return toBeAllocated->m_startAddr;
				}
				else {//There is some Allocations
					BlockDescriptor* mainBlock = m_allocatedBlockHead;
					while (mainBlock->m_next != nullptr) {
						mainBlock = reinterpret_cast<BlockDescriptor*>(mainBlock->m_next);
					}
					toBeAllocated->m_next = nullptr;
					mainBlock->m_next = toBeAllocated;
					char* addresses = reinterpret_cast<char*>(toBeAllocated->m_startAddr);
					//four while loops to add padding and gaurdband at the memory location
					while (addresses < reinterpret_cast<char*>(freeBlocks->m_startAddr) + i_size) {
						*addresses = _bCleanLandFill;
						addresses++;
					}
					while (addresses < reinterpret_cast<char*>(freeBlocks->m_startAddr) + i_size + paddingNeeded) {
						*addresses = _bAlignLandFill;
						addresses++;
					}
					return toBeAllocated->m_startAddr;
				}
			}
			else {
				return nullptr;
			}
		}
		freeBlocks = reinterpret_cast<BlockDescriptor*>(freeBlocks->m_next);
	} while (m_freeBlockHead != nullptr);
	return nullptr;
}

#endif


bool HeapManager::freeMemory(void* i_block) {
	if (m_allocatedBlockHead == nullptr)
		return false;

	BlockDescriptor* Freed = m_allocatedBlockHead;
	BlockDescriptor* prevToFreed = nullptr;
#if defined(_DEBUG)
	while (Freed != nullptr && reinterpret_cast<char*>(Freed->m_startAddr) + 4 != i_block) {
		prevToFreed = Freed;
		Freed = reinterpret_cast<BlockDescriptor*>(Freed->m_next);
	}
#else
	while (Freed != nullptr && reinterpret_cast<char*>(Freed->m_startAddr) != i_block) {
		prevToFreed = Freed;
		Freed = reinterpret_cast<BlockDescriptor*>(Freed->m_next);
	}
#endif
	//If first than change Head else change pointers to remove Freed Discriptor from list
	if (prevToFreed == nullptr) {
		m_allocatedBlockHead = reinterpret_cast<BlockDescriptor*>(Freed->m_next);
	}
	else if (Freed == nullptr) {
		return false;
	}
	else {
		prevToFreed->m_next = Freed->m_next;
	}

	//Creating Dead Land Fill to memory address after freeing the memory
	char* addresses = reinterpret_cast<char*>(Freed->m_startAddr);
	while (addresses < reinterpret_cast<char*>(Freed->m_startAddr) + Freed->m_size) {
		*addresses = _bDeadLandFill;
		addresses++;
	}


	BlockDescriptor* freeBlocks = m_freeBlockHead;
	BlockDescriptor* prevToFreeBlocks = nullptr;
	while (freeBlocks->m_startAddr < Freed->m_startAddr && freeBlocks != nullptr) {
		prevToFreeBlocks = freeBlocks;
		freeBlocks = reinterpret_cast<BlockDescriptor*>(freeBlocks->m_next);
	}

	//used for defragmentation of descriptors 
	BlockDescriptor* remainingDescriptors = m_blockDiscriptorMaintainer;
	while (remainingDescriptors->m_next != nullptr)
		remainingDescriptors = reinterpret_cast<BlockDescriptor*>(remainingDescriptors->m_next);

	//check for all 9 cases for freeing memory
	//cases 1 and 2 Freed Block is at start of freeblocks
	if (prevToFreeBlocks == nullptr) {
		// case 1 Memory locations are continuous 
		if (reinterpret_cast<char*>(Freed->m_startAddr) + Freed->m_size == freeBlocks->m_startAddr) {
			freeBlocks->m_startAddr = Freed->m_startAddr;
			freeBlocks->m_size = freeBlocks->m_size + Freed->m_size;
			Freed->m_next = nullptr;
			Freed->m_startAddr = nullptr;
			Freed->m_size = NULL;
			remainingDescriptors->m_next = Freed;
		}
		// case 2 Memory locations are not are not continuous
		else {
			Freed->m_next = freeBlocks;
			m_freeBlockHead = Freed;
		}
	}
	//cases 7 and 8 Freed Block is at the end of freeblocks
	else if (freeBlocks == nullptr) {
		//case 7 Memory locations are continuous
		if (reinterpret_cast<char*>(prevToFreeBlocks->m_startAddr) + prevToFreeBlocks->m_size == Freed->m_startAddr) {
			prevToFreeBlocks->m_size = prevToFreeBlocks->m_size + Freed->m_size;
			Freed->m_next = nullptr;
			Freed->m_startAddr = nullptr;
			Freed->m_size = NULL;
			remainingDescriptors->m_next = Freed;
		}
		//case 8 Memory locations are not continuous 
		else {
			prevToFreeBlocks->m_next = Freed;
			Freed->m_next = nullptr;
		}
	}
	//cases 3 to 6 Freed Block is between 2 Freeblocks
	else {
		//case 6 all 3 blocks are not continuous
		prevToFreeBlocks->m_next = Freed;
		Freed->m_next = freeBlocks;

		//case 3 all 3 blocks are continuous
		if (reinterpret_cast<char*>(prevToFreeBlocks->m_startAddr) + prevToFreeBlocks->m_size == Freed->m_startAddr &&
			reinterpret_cast<char*>(Freed->m_startAddr) + Freed->m_size == freeBlocks->m_startAddr) {
			prevToFreeBlocks->m_next = freeBlocks->m_next;
			prevToFreeBlocks->m_size = prevToFreeBlocks->m_size + Freed->m_size + freeBlocks->m_size;
			Freed->m_startAddr = freeBlocks->m_startAddr = nullptr;
			Freed->m_size = freeBlocks->m_size = NULL;
			freeBlocks->m_next = nullptr;
			remainingDescriptors->m_next = Freed;
			return true;
		}
		// case 4 and 5 any 2 blocks are continuous
		//case 4 prevToFree and Freed blocks are continuous
		if (reinterpret_cast<char*>(prevToFreeBlocks->m_startAddr) + prevToFreeBlocks->m_size == Freed->m_startAddr) {
			prevToFreeBlocks->m_size = prevToFreeBlocks->m_size + Freed->m_size;
			prevToFreeBlocks->m_next = freeBlocks;
			Freed->m_next = nullptr;
			Freed->m_startAddr = nullptr;
			Freed->m_size = NULL;
			remainingDescriptors->m_next = Freed;
		}
		//case 5 Freed and freeblocks are continuous
		if (reinterpret_cast<char*>(Freed->m_startAddr) + Freed->m_size == freeBlocks->m_startAddr) {
			freeBlocks->m_startAddr = Freed->m_startAddr;
			freeBlocks->m_size = freeBlocks->m_size + Freed->m_size;
			prevToFreeBlocks->m_next = freeBlocks;
			Freed->m_next = nullptr;
			Freed->m_startAddr = nullptr;
			Freed->m_size = NULL;
			remainingDescriptors->m_next = Freed;
		}
	}
	return true;

}


void HeapManager::Collect()
{
}
bool HeapManager::IsContain(void * i_ptr) const
{
	return true;
}
bool HeapManager::IsAllocated(void * i_block) const {
	bool allocated = false;
	if (m_allocatedBlockHead == nullptr)
		return false;

	BlockDescriptor* temp = reinterpret_cast<BlockDescriptor*>(m_allocatedBlockHead);
	while (temp != nullptr && !allocated) {
		void * startAdd = temp->m_startAddr;
		void * endAdd = (char *)startAdd + temp->m_size;
		while (startAdd != endAdd) {
			if (startAdd == i_block) {
				allocated = true;
				break;
			}
			startAdd = (char *)startAdd + 1;
		}
		temp = reinterpret_cast<BlockDescriptor*>(temp->m_next);
	}
	return allocated;
}
size_t HeapManager::getLargestBlock() const {
	BlockDescriptor* temp = reinterpret_cast<BlockDescriptor*>(m_freeBlockHead);
	size_t maxSize = 0;
	while (temp != nullptr) {
		if (maxSize < temp->m_size) {
			maxSize = temp->m_size;
		}
		temp = reinterpret_cast<BlockDescriptor*>(temp->m_next);
	}
	return maxSize;
}
size_t HeapManager::getTotalFreeMemory() const {
	BlockDescriptor* temp = reinterpret_cast<BlockDescriptor*>(m_freeBlockHead);
	size_t totalSize = 0;
	while (temp != nullptr) {
		totalSize += temp->m_size;
		temp = reinterpret_cast<BlockDescriptor*>(temp->m_next);
	}
	return totalSize;
}
void HeapManager::ShowFreeBlocks() const {
	BlockDescriptor* temp = reinterpret_cast<BlockDescriptor*>(m_freeBlockHead);
	if (temp == nullptr) {
		writeline("No Free Blocks");
	}
	else {
		int freeBlocks = 0;
		while (temp != nullptr) {
			if (temp->m_size > 0) {
				writeline("Free Block: %d. Is of Size %d at %p", freeBlocks, temp->m_size, temp->m_startAddr);
				cout << "Free Block: " << freeBlocks << ". Is of Size " << temp->m_size << " at " << temp->m_startAddr << endl;
				freeBlocks++;
			}
			temp = reinterpret_cast<BlockDescriptor*>(temp->m_next);
		}
	}
}
void HeapManager::ShowAllocatedBlocks() const {
	BlockDescriptor* temp = reinterpret_cast<BlockDescriptor*>(m_allocatedBlockHead);
	if (temp == nullptr) {
		writeline("No Allocated Blocks");
	}
	else {
		int AllocatedBlocks = 0;
		while (temp != nullptr) {
			if (temp->m_size > 0) {
				writeline("Allocated Block: %d. Is of Size %d at %p", AllocatedBlocks, temp->m_size, temp->m_startAddr);
				cout << "Allocated Block: " << AllocatedBlocks << ". Is of Size " << temp->m_size << " at " << temp->m_startAddr << endl;
				AllocatedBlocks++;
			}
			temp = reinterpret_cast<BlockDescriptor*>(temp->m_next);
		}
	}
}
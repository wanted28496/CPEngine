#pragma once
/**
FSA.h
purpose: Creating the Fixed Size Allocator for memory management
@author Mit Doshi
@version 1.1 12/16/2018
*/

class BitArray;
class HeapManager;

class FixedSizedAllocator {
public:
	FixedSizedAllocator();
	FixedSizedAllocator(size_t i_blockSize, size_t i_numBlocks, HeapManager* i_heap);
	~FixedSizedAllocator();
	void * alloc(size_t i_size);
	bool freeMemory(void * i_block);
	void destroy(HeapManager* i_heap);
	void* getStartingAddress() const { return m_startingAddress; }
	size_t getBlockSize() const { return m_blockSize; }
	size_t getNumBlocks() const { return m_numBlocks; }
private:
	size_t m_blockSize;
	size_t m_numBlocks;
	void* m_startingAddress;
	BitArray* m_bitArray;
};
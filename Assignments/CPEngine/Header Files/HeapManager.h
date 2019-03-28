#pragma once
/**
 HeapManager.h
 purpose: custom memory Management
 @author Mit Doshi
 @version 1.3 11/24/2018
*/


struct BlockDescriptor
{
public:
	void * m_startAddr;
#if _WIN64
	unsigned __int64 m_size;
#else
	unsigned __int32 m_size;
#endif

	void * m_next;
};

class HeapManager {
public:
	/**
	function to create a Heap of size given by user

	@param i_size a size_t type to allolcate length of heal 
	@param i_descriptor total number of descriptor present

	@return pointer to HeapManager
	*/
	static HeapManager * createHeap(void * memoryBlock, size_t i_size, unsigned int i_descriptor);
	HeapManager();
	HeapManager(void * memoryBlock, size_t i_size, unsigned int i_descriptor);
	HeapManager* operator=(HeapManager*);
	~HeapManager();

	void * alloc(size_t i_size);
	void * alloc(size_t i_size, unsigned int i_allign);
	bool freeMemory(void * i_block);
	void destroy();
	void Collect();

	bool IsContain(void * i_block) const;
	bool IsAllocated(void * i_block) const;
	size_t getLargestBlock() const;
	size_t getTotalFreeMemory() const;
	void ShowFreeBlocks() const;
	void ShowAllocatedBlocks() const;
	BlockDescriptor* getHead(BlockDescriptor* i_head) const { return i_head; }
	//static HeapManager* getInstance() { return _instance; }
private:
	void *m_head;
	size_t m_heapSize;
	unsigned int m_numDescriptor;
	unsigned int count = 0;
	//static HeapManager* _instance;
	BlockDescriptor *m_allocatedBlockHead;
	BlockDescriptor *m_freeBlockHead;
	BlockDescriptor *m_blockDiscriptorMaintainer;
};
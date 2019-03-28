#pragma once
/**
MemoryInstance.h
purpose: stores the static instances for all memory blocks
@author Mit Doshi
@version 1.1 12/16/2018
*/

class HeapManager;
class FixedSizedAllocator;


class HeapInstance {
public:
	static HeapManager* _instance;
	static void setHeapInstance(void* i_memory, size_t i_sizeHeap, unsigned int i_numDescriptors);
	static void destroyInstance();
};

class FSA16 {
public:
	static FixedSizedAllocator* _FSA16instance;
	static void SetFSA16Instance(size_t i_numBlocks);
	static void DestroyFSA16Instance();
};

class FSA32 {
public:
	static FixedSizedAllocator* _FSA32instance;
	static void SetFSA32Instance(size_t i_numBlocks);
	static void DestroyFSA32Instance();
};

class FSA96 {
public:
	static FixedSizedAllocator* _FSA96instance;
	static void SetFSA96Instance(size_t i_numBlocks);
	static void DestroyFSA96Instance();
};

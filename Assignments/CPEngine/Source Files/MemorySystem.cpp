#include "MemorySystem.h"
#include"MemoryInstance.h"

bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	HeapInstance::setHeapInstance(i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors);

	FSA16::SetFSA16Instance(100);

	FSA32::SetFSA32Instance(200);

	FSA96::SetFSA96Instance(400);
	// create your HeapManager and FixedSizeAllocators
	return true;
}

void Collect()
{
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
}

void DestroyMemorySystem()
{
	FSA16::DestroyFSA16Instance();
	FSA32::DestroyFSA32Instance();
	FSA96::DestroyFSA96Instance();
	HeapInstance::destroyInstance();
	// Destroy your HeapManager and FixedSizeAllocators
}


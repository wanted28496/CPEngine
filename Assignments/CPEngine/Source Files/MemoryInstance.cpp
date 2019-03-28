#pragma once
#include"MemoryInstance.h"
#include"HeapManager.h"
#include"FSA.h"
#include"Console.h"
#include<assert.h>

HeapManager* HeapInstance::_instance;
FixedSizedAllocator* FSA16::_FSA16instance = nullptr;
FixedSizedAllocator* FSA32::_FSA32instance = nullptr;
FixedSizedAllocator* FSA96::_FSA96instance = nullptr;

void HeapInstance::setHeapInstance(void* i_memory, size_t i_sizeHeap, unsigned int i_numDescriptors) {
	_instance = HeapManager::createHeap(i_memory, i_sizeHeap, i_numDescriptors);;
}

void HeapInstance::destroyInstance() {
	_instance->destroy();
	_instance = nullptr;
}

void FSA16::SetFSA16Instance(size_t i_numBlocks) {
	assert(HeapInstance::_instance);
	_FSA16instance = new FixedSizedAllocator(16, i_numBlocks, HeapInstance::_instance);
}

void FSA16::DestroyFSA16Instance() {
	_FSA16instance->destroy(HeapInstance::_instance);
	HeapInstance::_instance->freeMemory(_FSA16instance);
	_FSA16instance = nullptr;

}


void FSA32::SetFSA32Instance(size_t i_numBlocks) {
	assert(HeapInstance::_instance);
	_FSA32instance = new FixedSizedAllocator(32, i_numBlocks, HeapInstance::_instance);
}

void FSA32::DestroyFSA32Instance() {
	_FSA32instance->destroy(HeapInstance::_instance);
	HeapInstance::_instance->freeMemory(_FSA32instance);
	_FSA32instance = nullptr;

}

void FSA96::SetFSA96Instance(size_t i_numBlocks) {
	assert(HeapInstance::_instance);
	_FSA96instance = new FixedSizedAllocator(96, i_numBlocks, HeapInstance::_instance);
}

void FSA96::DestroyFSA96Instance() {
	_FSA96instance->destroy(HeapInstance::_instance);
	HeapInstance::_instance->freeMemory(_FSA96instance);
	_FSA96instance = nullptr;
}




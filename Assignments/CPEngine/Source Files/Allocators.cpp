///**
//Allocators.cpp
//purpose: Allocating memory using either Fixed Size Allocator or Heap Allocator
//@author Mit Doshi
//@version 1.2 12/16/2018
//*/
//
//
//#include <inttypes.h>
//#include"Allocators.h"
//#include <stdio.h>
//#include"MemoryInstance.h"
//#include"HeapManager.h"
//#include"FSA.h"
//
//
//
///**
//Select which memory block, FSA or Heap, to give memory from
//
//@param i_size block size of the memory to be allocated
//
//*/
//int selectMemoryBlockToAdd(size_t i_size) {
//	if (i_size <= 16 && FSA16::_FSA16instance != nullptr) {
//		return 1;
//	}
//	else if (i_size <= 32 && FSA32::_FSA32instance != nullptr) {
//		return 2;
//	}
//	else if (i_size <= 96 && FSA96::_FSA96instance != nullptr) {
//		return 3;
//	}
//	else {
//		return 0;
//	}
//}
//
///**
//Select from which memory block, FSA or Heap, the memory is to be freed
//
//@param i_ptr pointer to the starting address of the memory block to be free
//
//*/
//int selectMemoryBlockToDelete(void* i_ptr) {
//	if (i_ptr >= FSA16::_FSA16instance->getStartingAddress() &&
//		i_ptr <= reinterpret_cast<char*>(FSA16::_FSA16instance->getStartingAddress()) + 
//		FSA16::_FSA16instance->getBlockSize() * 
//		FSA16::_FSA16instance->getNumBlocks()
//		)
//		return 1;
//	if (i_ptr >= FSA32::_FSA32instance->getStartingAddress() &&
//		i_ptr <= reinterpret_cast<char*>(FSA32::_FSA32instance->getStartingAddress()) +
//		FSA32::_FSA32instance->getBlockSize() *
//		FSA32::_FSA32instance->getNumBlocks()
//		)
//		return 2;
//	if (i_ptr >= FSA96::_FSA96instance->getStartingAddress() &&
//		i_ptr <= reinterpret_cast<char*>(FSA96::_FSA96instance->getStartingAddress()) +
//		FSA96::_FSA96instance->getBlockSize() *
//		FSA96::_FSA96instance->getNumBlocks()
//		)
//		return 3;
//	return 0;
//}
//
///**
//Allocates memory 
//
//@param i_size block size of the memory to be allocated
//
//*/
//void * __cdecl malloc(size_t i_size)
//{
//	void* returnMemory = nullptr;
//#if _DEBUG
//	int choice = selectMemoryBlockToAdd(i_size + 8);
//	if (choice == 0) {
//		returnMemory = HeapInstance::_instance->alloc(i_size);
//	}
//	if (choice == 1) {
//		returnMemory = FSA16::_FSA16instance->alloc(i_size + 8);
//	}
//	if (choice == 2 && FSA32::_FSA32instance != nullptr) {
//		returnMemory = FSA32::_FSA32instance->alloc(i_size + 8);
//	}
//	if (choice == 3 && FSA96::_FSA96instance != nullptr) {
//		returnMemory = FSA96::_FSA96instance->alloc(i_size + 8);
//	}
//
//#else
//	int choice = selectMemoryBlockToAdd(i_size);
//	//std::cout << "Size: " << i_size << std::endl;
//	if (choice == 0) {
//		returnMemory = HeapInstance::_instance->alloc(i_size);
//	}
//	if (choice == 1) {
//		returnMemory = FSA16::_FSA16instance->alloc(i_size);
//	}
//	if (choice == 2 && FSA32::_FSA32instance != nullptr) {
//		returnMemory = FSA32::_FSA32instance->alloc(i_size);
//	}
//	if (choice == 3 && FSA96::_FSA96instance != nullptr) {
//		//std::cout << "FSA Instance: " << FSA96::_FSA96instance << std::endl;
//		returnMemory = FSA96::_FSA96instance->alloc(i_size);
//	}
//
//#endif
//	if (returnMemory == nullptr) {
//		returnMemory = HeapInstance::_instance->alloc(i_size);
//	}
//	return returnMemory;
//}
//
///**
//Frees memory
//
//@param i_ptr pointer to starting address
//
//*/
//void __cdecl free(void * i_ptr)
//{
//	int choice = selectMemoryBlockToDelete(i_ptr);
//	switch (choice) {
//	case 1: FSA16::_FSA16instance->freeMemory(i_ptr);
//		break;
//	case 2: FSA32::_FSA32instance->freeMemory(i_ptr);
//		break;
//	case 3: FSA96::_FSA96instance->freeMemory(i_ptr);
//		break;
//	default:
//		HeapInstance::_instance->freeMemory(i_ptr);
//	}
//}
//
///**
//Allocates memory
//
//@param i_size block size of the memory to be allocated
//
//*/
//void * operator new(size_t i_size)
//{
//	void* returnMemory = nullptr;
//#if _DEBUG
//	int choice = selectMemoryBlockToAdd(i_size + 8);
//	if (choice == 0) {
//		returnMemory = HeapInstance::_instance->alloc(i_size);
//	}
//	if (choice == 1) {
//		returnMemory = FSA16::_FSA16instance->alloc(i_size + 8);
//	}
//	if (choice == 2 && FSA32::_FSA32instance != nullptr) {
//		returnMemory = FSA32::_FSA32instance->alloc(i_size + 8);
//	}
//	if (choice == 3 && FSA96::_FSA96instance != nullptr) {
//		returnMemory = FSA96::_FSA96instance->alloc(i_size + 8);
//	}
//
//#else
//	int choice = selectMemoryBlockToAdd(i_size);
//	if (choice == 0) {
//		returnMemory = HeapInstance::_instance->alloc(i_size);
//	}
//	if (choice == 1) {
//		returnMemory = FSA16::_FSA16instance->alloc(i_size);
//	}
//	if (choice == 2 && FSA32::_FSA32instance != nullptr) {
//		returnMemory = FSA32::_FSA32instance->alloc(i_size);
//	}
//	if (choice == 3 && FSA96::_FSA96instance != nullptr) {
//		returnMemory = FSA96::_FSA96instance->alloc(i_size);
//	}
//
//#endif
//	if (returnMemory == nullptr) {
//		returnMemory = HeapInstance::_instance->alloc(i_size);
//	}
//	return returnMemory;
//}
//
//
///**
//Frees memory
//
//@param i_ptr pointer to starting address
//
//*/
//void operator delete(void * i_ptr)
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	printf("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
//	int choice = selectMemoryBlockToDelete(i_ptr);
//	switch (choice) {
//	case 1: FSA16::_FSA16instance->freeMemory(i_ptr);
//		break;
//	case 2: FSA32::_FSA32instance->freeMemory(i_ptr);
//		break;
//	case 3: FSA96::_FSA96instance->freeMemory(i_ptr);
//		break;
//	default:
//		HeapInstance::_instance->freeMemory(i_ptr);
//	}
//}
//
///**
//Allocates memory
//
//@param i_size block size of the memory to be allocated
//
//*/
//void * operator new[](size_t i_size)
//{
//	void* returnMemory = nullptr;
//#if _DEBUG
//	int choice = selectMemoryBlockToAdd(i_size + 8);
//	if (choice == 0) {
//		returnMemory = HeapInstance::_instance->alloc(i_size);
//	}
//	if (choice == 1) {
//		returnMemory = FSA16::_FSA16instance->alloc(i_size + 8);
//	}
//	if (choice == 2 && FSA32::_FSA32instance != nullptr) {
//		returnMemory = FSA32::_FSA32instance->alloc(i_size + 8);
//	}
//	if (choice == 3 && FSA96::_FSA96instance != nullptr) {
//		returnMemory = FSA96::_FSA96instance->alloc(i_size + 8);
//	}
//
//#else
//	int choice = selectMemoryBlockToAdd(i_size);
//
//	if (choice == 0) {
//		returnMemory = HeapInstance::_instance->alloc(i_size);
//	}
//	if (choice == 1) {
//		returnMemory = FSA16::_FSA16instance->alloc(i_size);
//	}
//	if (choice == 2 && FSA32::_FSA32instance != nullptr) {
//		returnMemory = FSA32::_FSA32instance->alloc(i_size);
//	}
//	if (choice == 3 && FSA96::_FSA96instance != nullptr) {
//		returnMemory = FSA96::_FSA96instance->alloc(i_size);
//	}
//
//#endif
//	if (returnMemory == nullptr) {
//		returnMemory = HeapInstance::_instance->alloc(i_size);
//	}
//	return returnMemory;
//}
//
//
///**
//Frees memory
//
//@param i_ptr starting address of the memory block
//
//*/
//void operator delete [](void * i_ptr)
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	printf("delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
//	int choice = selectMemoryBlockToDelete(i_ptr);
//	switch (choice) {
//	case 1: FSA16::_FSA16instance->freeMemory(i_ptr);
//		break;
//	case 2: FSA32::_FSA32instance->freeMemory(i_ptr);
//		break;
//	case 3: FSA96::_FSA96instance->freeMemory(i_ptr);
//		break;
//	default:
//		HeapInstance::_instance->freeMemory(i_ptr);
//	}
//}
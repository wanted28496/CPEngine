#pragma once
/**
BitArray.h
purpose: Creating a bit array for Fixed Size Allocator
@author Mit Doshi
@version 1.1 12/16/2018
*/


class HeapManager;

class BitArray {
public:
	BitArray();
	~BitArray();

	static BitArray * createBitArray(size_t i_numbits, HeapManager* i_Allocator, bool i_initToZero = false);

	void ClearAll(void) const;
	void SetAll(void) const;

	inline bool IsBitSet(size_t i_bitNUmber) const;
	inline bool IsBitClear(size_t i_bitNumber) const;
	
	void setBit(size_t i_bitNUmber) const;
	void ClearBit(size_t i_bitNUmber) const;

	bool GetFirstClearBit(size_t & o_bitNUmber) const;
	bool GetFirstSetBit(size_t & o_bitNUmber) const;

	void Destroy(HeapManager* i_heap);
private:
	unsigned int m_size;
	unsigned char* m_bits;
};
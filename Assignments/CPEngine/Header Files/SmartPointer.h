#pragma once
#include"Console.h"
#include<stdint.h>
#include<assert.h>

#pragma region Reference Counter
struct RefCounter {
	typedef uint64_t refCounter;
	refCounter smartCounter;
	refCounter weakCounter;

	RefCounter() {
		smartCounter = 0;
		weakCounter = 0;
	}

	RefCounter(refCounter i_smartCount, refCounter i_weakCount) {
		smartCounter = i_smartCount;
		weakCounter = i_weakCount;

	}

	RefCounter(const RefCounter &i_rhs) {
		smartCounter = i_rhs.smartCounter;
		weakCounter = i_rhs.weakCounter;
	}

	RefCounter& operator=(const RefCounter &i_rhs) {
		this->smartCounter = i_rhs.smartCounter;
		this->weakCounter = i_rhs.weakCounter;
		return *this;
	}

	RefCounter& operator=(const RefCounter *i_rhs) {
		this->smartCounter = i_rhs->smartCounter;
		this->weakCounter = i_rhs->weakCounter;
		return *this;
	}
};
#pragma endregion

#pragma region Forward Declaration
template <class U>
class WeakPointer;
#pragma endregion


template <class T>
class SmartPointer {

#pragma region Friend Class Declaration
	template <class U>
	friend class WeakPointer;

	template <class U>
	friend class SmartPointer;
#pragma endregion


public:
#pragma region Constructors and Destructors
	SmartPointer() {
		m_ptr = nullptr;
		m_refCounter = nullptr;
	}

	SmartPointer(T* i_ptr) :m_ptr(i_ptr) {
		m_refCounter = new RefCounter(1, 0);
	}

	SmartPointer(const SmartPointer<T> &i_rhs) {
		m_ptr = i_rhs.m_ptr;
		m_refCounter = i_rhs.m_refCounter;
		m_refCounter->smartCounter++;
	}

	//template <class U>
	//SmartPointer(const SmartPointer<U> &i_rhs) {
	//	m_ptr = i_rhs.m_ptr;
	//	m_refCounter = i_rhs.m_refCounter;
	//	m_refCounter->smartCounter++;
	//}

	SmartPointer(const WeakPointer<T> &i_rhs) {
		if (i_rhs.m_refCounter->smartCounter != 0) {
			m_refCounter = i_rhs.m_refCounter;
			m_ptr = i_rhs.m_ptr;

			m_refCounter->smartCounter++;
		}
	}

	~SmartPointer() {
		DestroyReference();
	}
#pragma endregion

#pragma region Overload Operators

#pragma region Assignment Operators
	SmartPointer& operator=(const SmartPointer<T> &i_rhs) {
		if (m_ptr = i_rhs.m_ptr) {
			return *this;
		} else {
			DestroyReference();
			this->m_ptr = i_rhs.m_ptr;
			this->m_refCounter = i_rhs.m_refCounter;
			this->m_refCounter->smartCounter++;
			return *this;
		}
	}

	template <class U>
	SmartPointer& operator=(const SmartPointer<U> &i_rhs) {
		if (m_ptr = i_rhs.m_ptr) {
			return *this;
		} else {
			DestroyReference();
			this->m_ptr = i_rhs.m_ptr;
			this->m_refCounter = i_rhs.m_refCounter;
			this->m_refCounter->smartCounter++;
			return *this;
		}
	}

	SmartPointer& operator=(const T *i_rhs) {
		if (m_ptr = i_rhs.m_ptr) {
			return *this;
		} else {
			DestroyReference();
			this->m_ptr = i_rhs;
			this->m_refCounter = new RefCounter(1, 0);
			return *this;
		}
	}
#pragma endregion

#pragma region Equality Operator
	bool operator==(const SmartPointer<T> &i_rhs) const {
		return m_ptr == i_rhs.m_ptr;
	}

	template <class U>
	bool operator==(const SmartPointer<U> &i_rhs) const {
		return m_ptr == i_rhs.m_ptr;
	}

	bool operator==(const WeakPointer<T> &i_rhs) const {
		return m_ptr == i_rhs.m_ptr;
	}

	template <class U>
	bool operator==(const WeakPointer<U> &i_rhs) const {
		return m_ptr == i_rhs.m_ptr;
	}

	bool operator==(T* i_rhs) const {
		return m_ptr == i_rhs;
	}

	bool operator==(std::nullptr_t nullPointer)const {
		return m_ptr == nullPointer;
	}
#pragma endregion

#pragma region Inequality Operator
	//Adding InEquality operator because we want SmartPointer X != SmartPointer Y to check  the X->m_ptr
	bool operator!=(const SmartPointer<T> &i_rhs) const {
		return m_ptr != i_rhs.m_ptr;
	}

	template <class U>
	bool operator!=(const SmartPointer<U> &i_rhs) const {
		return m_ptr != i_rhs.m_ptr;
	}

	bool operator!=(const WeakPointer<T> &i_rhs) const {
		return m_ptr != i_rhs.m_ptr;
	}

	template <class U>
	bool operator!=(const WeakPointer<U> &i_rhs) const {
		return m_ptr != i_rhs.m_ptr;
	}

	bool operator!=(T* i_rhs) const {
		return m_ptr != i_rhs;
	}

	bool operator!=(std::nullptr_t nullPointer)const {
		return m_ptr != nullPointer;
	}

	operator bool() const {
		return m_ptr != nullptr;
	}
#pragma endregion

#pragma region Access Operator
	T* operator->() const {
		return m_ptr;
	}
#pragma endregion

#pragma endregion

private:
	T* m_ptr;
	RefCounter *m_refCounter;

#pragma region Private Helper Functions
	void DestroyReference() {
		m_refCounter->smartCounter--;
		if (m_refCounter->smartCounter == 0) {
			delete m_ptr;
			if (m_refCounter->weakCounter == 0) {
				delete m_refCounter;
			}
		}
	}
#pragma endregion

};
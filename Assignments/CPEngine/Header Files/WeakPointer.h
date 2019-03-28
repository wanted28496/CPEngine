#pragma once
#include"SmartPointer.h"

template<class T>
class WeakPointer {
#pragma region Friend Class Reference
	template <class U>
	friend class SmartPointer;

	template <class U>
	friend class WeakPointer;
#pragma endregion

public:

#pragma region Constructors and Destructors
	WeakPointer() {
		m_ptr = nullptr;
		m_refCounter = nullptr;
	}

	WeakPointer(const SmartPointer<T> &i_owner) {
		m_ptr = i_owner.m_ptr;
		m_refCounter = i_owner.m_refCounter;
		m_refCounter->weakCounter++;
		//m_refCounter->smartCounter++;
	}

	/*template <class U>
	WeakPointer(const SmartPointer<U> &i_owner) {
		m_ptr = i_owner.m_ptr;
		m_refCounter = i_owner.m_refCounter;
		m_refCounter->weakCounter++;
	}*/

	WeakPointer(const WeakPointer &i_rhs) {
		m_ptr = i_rhs.m_ptr;
		m_refCounter = i_rhs.m_refCounter;
		m_refCounter->weakCounter++;
	}

	/*template <class U>
	WeakPointer(const WeakPointer<U> &i_rhs) {
		m_ptr = i_rhs.m_ptr;
		m_refCounter = i_rhs.m_refCounter;
		m_refCounter->weakCounter++;
	}*/

	SmartPointer<T> AquireOwnership() {
		if (m_refCounter->smartCounter > 0) {
			return SmartPointer<T>(*this);
		} else {
			return SmartPointer<T>();
		}
	}

	~WeakPointer() {
		DestroyReference();
	}
#pragma endregion

#pragma region Operator Overloading

#pragma region Assignment Operator
	WeakPointer& operator=(const WeakPointer<T> &i_rhs) {
		if (m_ptr = i_rhs.m_ptr) {
			return *this;
		} else {
			if (m_refCounter != nullptr) {
				
				DestroyReference();
				this->m_ptr = i_rhs.m_ptr;
				this->m_refCounter = i_rhs.m_refCounter;
				this->m_refCounter->weakCounter++;
				return *this;
			}
			
		}
	}

	template <class U>
	WeakPointer& operator=(const WeakPointer<U> &i_rhs) {
		if (m_ptr = i_rhs.m_ptr) {
			return *this;
		} else {
			if (m_refCounter != nullptr) {
				DestroyReference();
				this->m_ptr = i_rhs.m_ptr;
				this->m_refCounter = i_rhs.m_refCounter;
				this->m_refCounter->smartCounter++;
				return *this;
			}
			
		}
	}

#pragma endregion

#pragma region Equality Operator
	bool operator==(const WeakPointer<T> &i_rhs) const {
		return m_ptr == i_rhs.m_ptr;
	}

	template <class U>
	bool operator==(const WeakPointer<U> &i_rhs) const {
		return m_ptr == i_rhs.m_ptr;
	}

	bool operator==(const SmartPointer<T> &i_rhs) const {
		return m_ptr == i_rhs.m_ptr;
	}

	template <class U>
	bool operator==(const SmartPointer<U> &i_rhs) const {
		return m_ptr == i_rhs.m_ptr;
	}

	bool operator==(T* i_rhs) const {
		return m_ptr == i_rhs;
	}

	bool operator==(std::nullptr_t nullPointer)const {
		return m_ptr == nullPointer;
	}
#pragma endregion

#pragma region InEquality Operators
	//Adding InEquality operator because we want WeakPointer X != WeakPointer Y to check  the X->m_ptr
	bool operator!=(const WeakPointer<T> &i_rhs) const {
		return m_ptr != i_rhs.m_ptr;
	}

	template <class U>
	bool operator!=(const WeakPointer<U> &i_rhs) const {
		return m_ptr != i_rhs.m_ptr;
	}

	bool operator!=(const SmartPointer<T> &i_rhs) const {
		return m_ptr != i_rhs.m_ptr;
	}

	template <class U>
	bool operator!=(const SmartPointer<U> &i_rhs) const {
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

#pragma endregion

private:
	T* m_ptr;
	RefCounter *m_refCounter;

#pragma region Private Helper Functions
	void DestroyReference() {
		m_refCounter->weakCounter--;
		if (m_refCounter->smartCounter == 0 && m_refCounter->smartCounter == 0) {
			delete m_ptr;
			delete m_refCounter;
		}
	}
#pragma endregion

};
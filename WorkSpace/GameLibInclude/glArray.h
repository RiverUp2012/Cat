
#pragma once

#include "glException.h"
#include <malloc.h>
#include <new.h>

//
// @brief 数组模板类
//
template <typename _U>
class glArray {
public:
	static const int defaultGrowUnits = 16;
public:
	glArray() {
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;
	}
	glArray(const int capacity) {
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;
		resize(capacity);
	}
	glArray(const int capacity, const _U & data) {
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;
		resize(capacity, data);
	}
	glArray(const glArray & other) {
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;
		if (resize(other.getCapacity())) {
			for (int i = 0; i < other.getCapacity(); ++i) {
				mArray[i] = other.getAt(i);
			}
		}
	}
	virtual ~glArray() {
		clear();
	}
public:
	void clear(void) {
		if (mArray) {
			for (int i = 0; i < mCapacity; ++i) {
				mArray[i].~_U();
			}
			free(mArray);
		}
		mArray = 0;
		mCapacity = 0;
		mItems = 0;
		mGrowUnits = defaultGrowUnits;
	}
	bool resize(const int capacity) {
		clear();
		if (capacity > 0) {
			mArray = (_U *)malloc(sizeof(_U)* capacity);
			if (mArray) {
				for (int i = 0; i < capacity; ++i) {
					new (&mArray[i]) _U;
				}
				mCapacity = capacity;
				return true;
			}
			else {
				throw glException(L"bad malloc()");
			}
		}
		return false;
	}
	bool resize(const int capacity, const _U & data) {
		if (resize(capacity)) {
			for (int i = 0; i < capacity; ++i) {
				mArray[i] = data;
			}
			return true;
		}
		return false;
	}
	bool add(const _U & data) {
		const int newCapacity = mCapacity + defaultGrowUnits;
		_U * newArray = 0;
		if ((!mArray || mItems >= mCapacity) && newCapacity > 0) {
			newArray = (_U *)realloc(mArray, sizeof(_U)* newCapacity);
			if (newArray) {
				for (int i = mItems; i < newCapacity; ++i) {
					new &(newCapacity[i]) _U;
				}
				mArray = newArray;
				mCapacity = newCapacity;
			}
			else {
				throw glException(L"bad realloc()");
			}
		}
		if (mArray && mItems < mCapacity) {
			mArray[mItems] = data;
			++mItems;
			return true;
		}
		return false;
	}
	const _U * getArray(void) const {
		return mArray;
	}
	int getCapacity(void) const {
		return mCapacity;
	}
	int getItems(void) const {
		return mItems;
	}
	const _U & getAt(const int index) const {
		if (!mArray || index < 0 || index >= mCapacity) {
			throw glException(L"index out of range");
		}
		return mArray[index];
	}
	_U & getAtRef(const int index) {
		if (!mArray || index < 0 || index >= mCapacity) {
			throw glException(L"index out of range");
		}
		return mArray[index];
	}
	bool setAt(const int index, const _U & data) {
		if (mArray && index >= 0 && index < mCapacity) {
			mArray[index] = data;
			return true;
		}
		return false;
	}
	void setGrowUnits(const int growUnits) {
		mGrowUnits = growUnits;
		if(mGrowUnits < 0) {
			mGrowUnits = 0;
		}
	}
	int getGrowUnits(void) const {
		return mGrowUnits;
	}
private:
	_U * mArray;
	int mCapacity;
	int mItems;
	int mGrowUnits;
};

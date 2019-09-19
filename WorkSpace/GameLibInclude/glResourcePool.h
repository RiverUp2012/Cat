
#pragma once

#include "glArray.h"

//
// @brief 资源池模板类
//
template <typename _U>
class glResourcePool {
private:
	struct glItem {
		_U mResource;
		int mID;
		bool mInUse;
	};
public:
	glResourcePool(const int capacity = 64) {
		if (capacity > 0) {
			if (mItemArray.resize(capacity)) {
				for (int i = 0; i < mItemArray.getCapacity(); ++i) {
					glItem & item = mItemArray.getAtRef(i);
					item.mID = 0;
					item.mInUse = false;
				}
			}
		}
		mNextItemID = 1;
	}
	virtual ~glResourcePool() {
		mItemArray.clear();
	}
public:
	void clear(void) {
		for (int i = 0; i < mItemArray.getCapacity(); ++i) {
			glItem & item = mItemArray.getAtRef(i);
			item.mID = 0;
			item.mInUse = false;
		}
		mNextItemID = 1;
	}
	bool insertResource(const _U & resource, int & id) {
		if (mNextItemID < 0xFFFFFFFF) {
			for (int i = 0; i < mItemArray.getCapacity(); ++i) {
				glItem & item = mItemArray.getAtRef(i);
				if (!item.mInUse) {
					item.mResource = resource;
					item.mID = mNextItemID;
					item.mInUse = true;
					++mNextItemID;
					id = item.mID;
					return true;
				}
			}
		}
		return false;
	}
	bool getResource(const int id, _U & resource, const bool markResourceUnuse = true) {
		for (int i = 0; i < mItemArray.getCapacity(); ++i) {
			glItem & item = mItemArray.getAtRef(i);
			if (item.mInUse && id == item.mID) {
				resource = item.mResource;
				if (markResourceUnuse) {
					item.mInUse = false;
					item.mID = 0;
				}
				return true;
			}
		}
		return false;
	}
	bool markResourceUnuseByID(const int id) {
		for (int i = 0; i < mItemArray.getCapacity(); ++i) {
			glItem & item = mItemArray.getAtRef(i);
			if (item.mInUse && id == item.mID) {
				item.mInUse = false;
				item.mID = 0;
				return true;
			}
		}
		return false;
	}
	bool markResourceUnuseByID(const _U & resource) {
		for (int i = 0; i < mItemArray.getCapacity(); ++i) {
			glItem & item = mItemArray.getAtRef(i);
			if (item.mInUse && resource == item.mResource) {
				item.mInUse = false;
				item.mID = 0;
				return true;
			}
		}
		return false;
	}
private:
	glArray<glItem> mItemArray;
	int mNextItemID;
};

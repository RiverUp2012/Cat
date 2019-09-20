
#pragma once

#include "glArray.h"

template <typename _U>
class glPage {
public:
	glPage() {
		mTotalPage = 0;
		mCurrentPage = 0;
		mCurrentItem = 0;
		mItemPerPage = 0;
	}
	virtual ~glPage() {
	}
public:
	void create(const int totalItem, const int itemPerPage) {
		mItemArray.clear();
		mTotalPage = 0;
		mCurrentPage = 0;
		mCurrentItem = 0;
		mItemPerPage = itemPerPage;
	}
private:
	void reset(void) {
		mTotalPage = 0;
		mCurrentPage = 0;
		mCurrentItem = 0;
		mItemPerPage = 0;
	}
private:
	glArray<_U> mItemArray;
	int mTotalPage;
	int mCurrentPage;
	int mCurrentItem;
	int mItemPerPage;
};

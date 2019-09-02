
#include "../TurboLib.h"

#define T_MAX_PAGE (32)

typedef struct _T_PAGE
{
	T_OBJECT mItemArray;
	int mCurrentItem;
	int mCurrentPage;
	int mTotalPage;
	int mItemPerPage;
	int mInUse;
}
T_PAGE;

static T_PAGE gPageArray[T_MAX_PAGE] = { 0 };

static T_PAGE * TFindUnusePage(void)
{
	for (int i = 0; i < T_MAX_PAGE; ++i)
	{
		if (!gPageArray[i].mInUse)
		{
			return &gPageArray[i];
		}
	}

	return 0;
}

T_OBJECT TPageCreate(
	const int itemPerPage)
{
	T_PAGE * pageImpl = TFindUnusePage();
	if (pageImpl)
	{
		pageImpl->mItemArray = TArrayCreate(0);
		pageImpl->mItemPerPage = itemPerPage;
		pageImpl->mInUse = T_TRUE;
	}

	return (T_OBJECT)pageImpl;
}

void TPageDestroy(
	T_OBJECT page,
	TArrayCallbackProc forEachProc,
	void * userData)
{
	T_PAGE * pageImpl = (T_PAGE *)page;
	if (pageImpl)
	{
		if (pageImpl->mItemArray)
		{
			if (forEachProc)
			{
				TArrayForEach(pageImpl->mItemArray, forEachProc, userData);
			}

			TArrayDestroy(pageImpl->mItemArray, 0, 0);
			pageImpl->mItemArray = 0;
		}

		TMemset(pageImpl, sizeof(T_PAGE), 0);
	}
}

void TPageNextItem(
	T_OBJECT page)
{
	int totalItem = 0;

	T_PAGE * pageImpl = (T_PAGE *)page;
	if (pageImpl && pageImpl->mItemArray)
	{
		totalItem = TArrayGetAddedItems(pageImpl->mItemArray);
		if (pageImpl->mCurrentItem <= totalItem - 1)
		{
			++pageImpl->mCurrentItem;
			pageImpl->mCurrentPage = pageImpl->mCurrentItem / pageImpl->mItemPerPage;
		}
	}
}

void TPagePrevItem(
	T_OBJECT page)
{
	T_PAGE * pageImpl = (T_PAGE *)page;
	if (pageImpl)
	{
		if (pageImpl->mCurrentItem > 0)
		{
			--pageImpl->mCurrentItem;
			pageImpl->mCurrentPage = pageImpl->mCurrentItem / pageImpl->mItemPerPage;
		}
	}
}

void TPageNextPage(
	T_OBJECT page)
{
	int totalItem = 0;

	T_PAGE * pageImpl = (T_PAGE *)page;
	if (pageImpl && pageImpl->mItemArray)
	{
		if (pageImpl->mCurrentPage < pageImpl->mTotalPage - 1)
		{
			++pageImpl->mCurrentPage;
			pageImpl->mCurrentItem = pageImpl->mCurrentPage * pageImpl->mItemPerPage;

			totalItem = TArrayGetAddedItems(pageImpl->mItemArray);
			if (pageImpl->mCurrentItem >= totalItem)
			{
				pageImpl->mCurrentItem = totalItem - 1;
			}
		}
	}
}

void TPagePrevPage(
	T_OBJECT page)
{
	T_PAGE * pageImpl = (T_PAGE *)page;
	if (pageImpl)
	{
		if (pageImpl->mCurrentPage > 0)
		{
			--pageImpl->mCurrentPage;
			pageImpl->mCurrentItem = pageImpl->mCurrentPage * pageImpl->mItemPerPage;
		}
	}
}

int TPageAddItem(
	T_OBJECT page,
	void * item)
{
	int totalItem = 0;

	T_PAGE * pageImpl = (T_PAGE *)page;
	if (pageImpl && pageImpl->mItemArray)
	{
		if (TArrayAddData(pageImpl->mItemArray, item))
		{
			totalItem = TArrayGetAddedItems(pageImpl->mItemArray);

			pageImpl->mCurrentItem = 0;
			pageImpl->mCurrentPage = 0;
			pageImpl->mTotalPage = (totalItem + (pageImpl->mItemPerPage - 1)) / pageImpl->mItemPerPage;

			return T_TRUE;
		}
	}

	return T_FALSE;
}

void * TPageGetCurrentItem(
	T_OBJECT page)
{
	T_PAGE * pageImpl = (T_PAGE *)page;
	if (pageImpl &&
		pageImpl->mItemArray &&
		pageImpl->mCurrentItem < TArrayGetAddedItems(pageImpl->mItemArray))
	{
		return TArrayGetAt(pageImpl->mItemArray, pageImpl->mCurrentItem);
	}
	
	return 0;
}

int TPageGetTotalItem(
	T_OBJECT page)
{
	T_PAGE * pageImpl = (T_PAGE *)page;
	if (pageImpl && pageImpl->mItemArray)
	{
		return TArrayGetAddedItems(pageImpl->mItemArray);
	}

	return 0;
}

int TPageGetCurrentPage(
	T_OBJECT page)
{
	T_PAGE * pageImpl = (T_PAGE *)page;

	return pageImpl ? pageImpl->mCurrentPage : 0;
}

int TPageGetTotalPage(
	T_OBJECT page)
{
	T_PAGE * pageImpl = (T_PAGE *)page;

	return pageImpl ? pageImpl->mCurrentItem : 0;
}

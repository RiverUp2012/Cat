
#include "../TurboLib.h"

typedef struct _T_LIST_NODE
{
	void * mData;
	struct _T_LIST_NODE * mPrev;
	struct _T_LIST_NODE * mNext;
}
T_LIST_NODE;

typedef struct _T_LIST
{
	int mNodeCount;
	T_LIST_NODE * mHeadNode;
	T_LIST_NODE * mTailNode;
}
T_LIST;

T_OBJECT TListCreate(void)
{
	T_LIST * listImpl = (T_LIST *)TMalloc0(sizeof(T_LIST));
	if (listImpl)
	{
		return (T_OBJECT)listImpl;
	}

	return 0;
}

void TListDestroy(
	T_OBJECT list,
	TListCallbackProc forEachProc,
	void * userData)
{
	T_LIST * listImpl = (T_LIST *)list;
	if (listImpl)
	{
		T_LIST_NODE * node = listImpl->mHeadNode;
		while (node)
		{
			T_LIST_NODE * nextNode = node->mNext;

			if (0 != forEachProc)
			{
				forEachProc(list, node->mData, userData);
			}

			TFree(node);
			node = 0;

			node = nextNode;
		}

		TFree(listImpl);
		listImpl = 0;
	}
}

int TListGetNodeCount(
	T_OBJECT list)
{
	T_LIST * listImpl = (T_LIST *)list;

	return listImpl ? listImpl->mNodeCount : 0;
}

void TListForEach(
	T_OBJECT list,
	TListCallbackProc forEachProc,
	void * userData)
{
	T_LIST * listImpl = (T_LIST *)list;
	if (listImpl && 0 != forEachProc)
	{
		T_LIST_NODE * node = listImpl->mHeadNode;
		while (node)
		{
			if (T_TRUE != forEachProc(list, node->mData, userData))
			{
				break;
			}

			node = node->mNext;
		}
	}
}

int TListAddDataToTail(
	T_OBJECT list,
	void * data)
{
	T_LIST * listImpl = (T_LIST *)list;
	if (listImpl)
	{
		T_LIST_NODE * newNode = (T_LIST_NODE *)TMalloc0(sizeof(T_LIST_NODE));
		if (newNode)
		{
			newNode->mData = data;

			if (!listImpl->mTailNode)
			{
				listImpl->mHeadNode = newNode;
				listImpl->mTailNode = newNode;
			}
			else
			{
				newNode->mPrev = listImpl->mTailNode;
				listImpl->mTailNode->mNext = newNode;
				listImpl->mTailNode = newNode;
			}

			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TListAddDataToHead(
	T_OBJECT list,
	void * data)
{
	T_LIST * listImpl = (T_LIST *)list;
	if (listImpl)
	{
		T_LIST_NODE * newNode = (T_LIST_NODE *)TMalloc0(sizeof(T_LIST_NODE));
		if (newNode)
		{
			newNode->mData = data;

			if (!listImpl->mTailNode)
			{
				listImpl->mHeadNode = newNode;
				listImpl->mTailNode = newNode;
			}
			else
			{
				newNode->mNext = listImpl->mHeadNode;
				listImpl->mHeadNode->mPrev = newNode;
				listImpl->mHeadNode = newNode;
			}

			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TListIsContainData(
	T_OBJECT list,
	const void * data)
{
	T_LIST * listImpl = (T_LIST *)list;
	if (listImpl)
	{
		T_LIST_NODE * node = listImpl->mHeadNode;
		while (node)
		{
			if (data == node->mData)
			{
				return T_TRUE;
			}

			node = node->mNext;
		}
	}

	return T_FALSE;
}

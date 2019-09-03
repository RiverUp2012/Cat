
#include "../TurboLib.h"

#define T_ARRAY_DEFAULT_GROW_UNITS (16)

typedef struct _T_ARRAY
{
	int mCapacity;
	int mAddedItems;
	unsigned char ** mArray;
	int mGrowUnits;
}
T_ARRAY;

T_OBJECT TArrayCreate(
	const int capacity)
{
	T_ARRAY * arrayImpl = (T_ARRAY *)TMalloc0(sizeof(T_ARRAY));
	if (arrayImpl)
	{
		arrayImpl->mGrowUnits = T_ARRAY_DEFAULT_GROW_UNITS;

		if (capacity > 0)
		{
			arrayImpl->mArray = (unsigned char **)TMalloc0(sizeof(unsigned char *)* capacity);
			if (arrayImpl->mArray)
			{
				for (int i = 0; i < capacity; ++i)
				{
					arrayImpl->mArray[i] = 0;
				}

				arrayImpl->mCapacity = capacity;
			}
		}

		return (T_OBJECT)arrayImpl;
	}

	return 0;
}

void TArrayDestroy(
	T_OBJECT array,
	TArrayCallbackProc forEachProc,
	void * userData)
{
	T_ARRAY * arrayImpl = (T_ARRAY *)array;
	if (arrayImpl)
	{
		if (arrayImpl->mArray)
		{
			if (forEachProc)
			{
				for (int i = 0; i < arrayImpl->mCapacity; ++i)
				{
					if (!forEachProc(array, (void *)arrayImpl->mArray[i], userData))
					{
						break;
					}
				}
			}

			TFree(arrayImpl->mArray);
			arrayImpl->mArray = 0;
		}

		TFree(arrayImpl);
		arrayImpl = 0;
	}
}

void TArrayClear(
	T_OBJECT array,
	TArrayCallbackProc forEachProc,
	void * userData)
{
	T_ARRAY * arrayImpl = (T_ARRAY *)array;
	if (arrayImpl)
	{
		if (arrayImpl->mArray)
		{
			if (forEachProc)
			{
				for (int i = 0; i < arrayImpl->mCapacity; ++i)
				{
					if (!forEachProc(array, (void *)arrayImpl->mArray[i], userData))
					{
						break;
					}
				}
			}

			TFree(arrayImpl->mArray);
			arrayImpl->mArray = 0;
		}

		arrayImpl->mAddedItems = 0;
		arrayImpl->mCapacity = 0;
		arrayImpl->mGrowUnits = T_ARRAY_DEFAULT_GROW_UNITS;
	}
}

int TArrayAddData(
	T_OBJECT array,
	void * data)
{
	int newCapacity = 0;
	unsigned char ** newArray = 0;

	T_ARRAY * arrayImpl = (T_ARRAY *)array;
	if (arrayImpl)
	{
		if (!arrayImpl->mArray || arrayImpl->mAddedItems >= arrayImpl->mCapacity)
		{
			newCapacity = arrayImpl->mCapacity + arrayImpl->mGrowUnits;
			if (newCapacity > 0)
			{
				newArray = (unsigned char **)TRealloc(arrayImpl->mArray, sizeof(unsigned char *) * newCapacity);
				if (newArray)
				{
					for (int i = arrayImpl->mAddedItems; i < newCapacity; ++i)
					{
						newArray[i] = 0;
					}

					arrayImpl->mArray = newArray;
					arrayImpl->mCapacity = newCapacity;
				}
			}
		}

		if (arrayImpl->mArray && arrayImpl->mAddedItems < arrayImpl->mCapacity)
		{
			arrayImpl->mArray[arrayImpl->mAddedItems] = (unsigned char *)data;
			++arrayImpl->mAddedItems;

			return T_TRUE;
		}
	}

	return T_FALSE;
}

void * TArrayGetAt(
	T_OBJECT array,
	const int index)
{
	T_ARRAY * arrayImpl = (T_ARRAY *)array;
	if (arrayImpl && arrayImpl->mArray && index < arrayImpl->mCapacity)
	{
		return (void *)arrayImpl->mArray[index];
	}

	return 0;
}

int TArraySetAt(
	T_OBJECT array,
	const int index,
	void * data)
{
	T_ARRAY * arrayImpl = (T_ARRAY *)array;
	if (arrayImpl && arrayImpl->mArray && index < arrayImpl->mCapacity)
	{
		arrayImpl->mArray[index] = (unsigned char *)data;

		return T_TRUE;
	}

	return T_FALSE;
}

int TArrayGetCapacity(
	T_OBJECT array)
{
	T_ARRAY * arrayImpl = (T_ARRAY *)array;

	return arrayImpl ? arrayImpl->mCapacity : 0;
}

int TArrayGetAddedItems(
	T_OBJECT array)
{
	T_ARRAY * arrayImpl = (T_ARRAY *)array;

	return arrayImpl ? arrayImpl->mAddedItems : 0;
}

void TArrayForEach(
	T_OBJECT array,
	TArrayCallbackProc forEachProc,
	void * userData)
{
	T_ARRAY * arrayImpl = (T_ARRAY *)array;
	if (arrayImpl && arrayImpl->mArray && forEachProc)
	{
		for (int i = 0; i < arrayImpl->mCapacity; ++i)
		{
			if (!forEachProc(array, (void *)arrayImpl->mArray[i], userData))
			{
				break;
			}
		}
	}
}

void TArraySetGrowUnits(
	T_OBJECT array,
	const int growUnits)
{
	T_ARRAY * arrayImpl = (T_ARRAY *)array;
	if (arrayImpl)
	{
		arrayImpl->mGrowUnits = growUnits;
	}
}

int TArrayGetGrowUnits(
	T_OBJECT array)
{
	T_ARRAY * arrayImpl = (T_ARRAY *)array;

	return arrayImpl ? arrayImpl->mGrowUnits : 0;
}

void TArrayFreeAllData(
	T_OBJECT array,
	const int byCapacity)
{
	int forSteps = 0;

	if (array)
	{
		forSteps = byCapacity ? TArrayGetCapacity(array) : TArrayGetAddedItems(array);
		for (int i = 0; i < forSteps; ++i)
		{
			void * data = TArrayGetAt(array, i);
			if (data)
			{
				TFree(data);
				data = 0;

				TArraySetAt(array, i, 0);
			}
		}
	}
}

int TArrayFindEmpty(
	T_OBJECT array,
	const int byCapacity)
{
	int forSteps = 0;

	if (array)
	{
		forSteps = byCapacity ? TArrayGetCapacity(array) : TArrayGetAddedItems(array);
		for (int i = 0; i < forSteps; ++i)
		{
			if (!TArrayGetAt(array, i))
			{
				return i;
			}
		}
	}

	return -1;
}

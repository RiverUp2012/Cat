
#include "../TurboLib.h"

typedef struct _T_BUCKET
{
	void * mData;
	wchar_t * mKey;
	struct _T_BUCKET * mNext;
}
T_BUCKET;

typedef struct _T_DICTIONARY
{
	int mBucketCount;
	T_BUCKET ** mBucketList;
}
T_DICTIONARY;

T_OBJECT TDictionaryCreate(
	const int bucketCount)
{
	if (bucketCount > 0)
	{
		T_DICTIONARY * dictionaryImpl = (T_DICTIONARY *)TMalloc0(sizeof(T_DICTIONARY));
		if (dictionaryImpl)
		{
			dictionaryImpl->mBucketList = (T_BUCKET **)TMalloc0(sizeof(T_BUCKET *)* bucketCount);
			if (dictionaryImpl->mBucketList)
			{
				dictionaryImpl->mBucketCount = bucketCount;

				return (T_OBJECT)dictionaryImpl;
			}

			TFree(dictionaryImpl);
			dictionaryImpl = 0;
		}
	}

	return 0;
}

void TDictionaryDestroy(
	T_OBJECT dictionary,
	TDictionaryCallbackProc forEachProc,
	void * userData)
{
	T_DICTIONARY * dictionaryImpl = (T_DICTIONARY *)dictionary;
	if (dictionaryImpl)
	{
		if (dictionaryImpl->mBucketList)
		{
			for (int i = 0; i < dictionaryImpl->mBucketCount; ++i)
			{
				T_BUCKET * bucket = dictionaryImpl->mBucketList[i];
				while (bucket)
				{
					T_BUCKET * nextBucket = bucket->mNext;

					if (forEachProc)
					{
						forEachProc(dictionary, bucket->mKey, bucket->mData, userData);
					}

					if (bucket->mKey)
					{
						TFree(bucket->mKey);
						bucket->mKey = 0;
					}

					TFree(bucket);
					bucket = 0;

					bucket = nextBucket;
				}
			}

			TFree(dictionaryImpl->mBucketList);
			dictionaryImpl->mBucketList = 0;
		}

		TFree(dictionaryImpl);
		dictionaryImpl = 0;
	}
}

int TDictionaryPutData(
	T_OBJECT dictionary,
	const wchar_t * key,
	void * data)
{
	int ret = T_FALSE;
	int keyHash = 0;
	int bucketIndex = 0;
	T_BUCKET * newBucket = 0;

	T_DICTIONARY * dictionaryImpl = (T_DICTIONARY *)dictionary;
	if (dictionaryImpl && dictionaryImpl->mBucketList && key)
	{
		keyHash = THashStringW(key);
		bucketIndex = keyHash % dictionaryImpl->mBucketCount;
		newBucket = (T_BUCKET *)TMalloc0(sizeof(T_BUCKET));
		if (newBucket)
		{
			newBucket->mKey = TStringDuplicateW(key);
			if (newBucket->mKey)
			{
				newBucket->mData = data;
				newBucket->mNext = 0;

				if (!dictionaryImpl->mBucketList[bucketIndex])
				{
					dictionaryImpl->mBucketList[bucketIndex] = newBucket;
				}
				else
				{
					newBucket->mNext = dictionaryImpl->mBucketList[bucketIndex];
					dictionaryImpl->mBucketList[bucketIndex] = newBucket;
				}

				ret = T_TRUE;
			}
		}

		if (T_TRUE != ret)
		{
			if (newBucket)
			{
				if (newBucket->mKey)
				{
					TFree(newBucket->mKey);
					newBucket->mKey = 0;
				}

				TFree(newBucket);
				newBucket = 0;
			}
		}
	}

	return ret;
}

void * TDictionaryGetData(
	T_OBJECT dictionary,
	const wchar_t * key,
	int * error)
{
	int keyHash = 0;
	int bucketIndex = 0;
	T_BUCKET * bucket = 0;

	T_DICTIONARY * dictionaryImpl = (T_DICTIONARY *)dictionary;
	if (dictionaryImpl && dictionaryImpl->mBucketList && key)
	{
		keyHash = THashStringW(key);
		bucketIndex = keyHash % dictionaryImpl->mBucketCount;
		bucket = dictionaryImpl->mBucketList[bucketIndex];
		while (bucket)
		{
			if (T_TRUE == TStringIsEqualW(key, bucket->mKey))
			{
				if (error)
				{
					*error = T_TRUE;
				}

				return bucket->mData;
			}

			bucket = bucket->mNext;
		}

		if (error)
		{
			*error = T_FALSE;
		}
	}

	return 0;
}

int TDictionaryContain(
	T_OBJECT dictionary,
	const wchar_t * key)
{
	int keyHash = 0;
	int bucketIndex = 0;
	T_BUCKET * bucket = 0;

	T_DICTIONARY * dictionaryImpl = (T_DICTIONARY *)dictionary;
	if (dictionaryImpl && key)
	{
		keyHash = THashStringW(key);
		bucketIndex = keyHash % dictionaryImpl->mBucketCount;
		bucket = dictionaryImpl->mBucketList[bucketIndex];
		while (bucket)
		{
			if (T_TRUE == TStringIsEqualW(key, bucket->mKey))
			{
				return T_TRUE;
			}

			bucket = bucket->mNext;
		}
	}

	return T_FALSE;
}

int TDictionaryRemove(
	T_OBJECT dictionary,
	const wchar_t * key,
	TDictionaryCallbackProc removeProc,
	void * userData)
{
	int ret = T_FALSE;
	int keyHash = 0;
	int bucketIndex = 0;
	T_BUCKET * bucket = 0;
	T_BUCKET * nextBucket = 0;

	T_DICTIONARY * dictionaryImpl = (T_DICTIONARY *)dictionary;
	if (dictionaryImpl && key)
	{
		keyHash = THashStringW(key);
		bucketIndex = keyHash % dictionaryImpl->mBucketCount;
		bucket = dictionaryImpl->mBucketList[bucketIndex];
		while (bucket)
		{
			nextBucket = bucket->mNext;

			if (T_TRUE == TStringIsEqualW(key, bucket->mKey))
			{
				ret = T_TRUE;

				if (removeProc)
				{
					if (T_TRUE == removeProc(dictionary, bucket->mKey, bucket->mData, userData))
					{
						break;
					}
				}

				if (bucket == dictionaryImpl->mBucketList[bucketIndex])
				{
					dictionaryImpl->mBucketList[bucketIndex] = bucket->mNext;
				}

				if (bucket->mKey)
				{
					TFree(bucket->mKey);
					bucket->mKey = 0;
				}

				TFree(bucket);
				bucket = 0;
			}

			bucket = nextBucket;
		}
	}

	return ret;
}

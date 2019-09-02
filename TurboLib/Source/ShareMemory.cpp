
#include "../TurboLib.h"
#include "../Include/Private.h"

#define T_MAX_SHARE_MEMORY_NAME_SIZE (64)
#define T_MAX_SHARE_MEMORY (32)

typedef struct _T_SHARE_MEMORY
{
	// 共享内存名称
	wchar_t mName[T_MAX_SHARE_MEMORY_NAME_SIZE];
	// 共享内存句柄
	HANDLE mFileMapHandle;
	// 为真表示创建，为假表示打开
	int mCreateFlag;
	// 共享内存大小
	int mSize;
	// 共享内存指针
	void * mViewOfFile;
}
T_SHARE_MEMORY;

static T_SHARE_MEMORY gShareMemoryArray[T_MAX_SHARE_MEMORY] = { 0 };

static T_SHARE_MEMORY * TFindUnuseShareMemory(void)
{
	for (int i = 0; i < T_MAX_SHARE_MEMORY; ++i)
	{
		if (!gShareMemoryArray[i].mFileMapHandle)
		{
			return &gShareMemoryArray[i];
		}
	}

	return 0;
}

T_OBJECT TShareMemoryOpenW(
	const wchar_t * name,
	const int sizeForCreate)
{
	if (name)
	{
		T_SHARE_MEMORY * shareMemoryImpl = TFindUnuseShareMemory();
		if (shareMemoryImpl)
		{
			shareMemoryImpl->mFileMapHandle = OpenFileMappingW(
				FILE_MAP_READ | FILE_MAP_WRITE,
				FALSE,
				name);
			if (!shareMemoryImpl->mFileMapHandle)
			{
				shareMemoryImpl->mFileMapHandle = CreateFileMappingW(
					INVALID_HANDLE_VALUE,
					0,
					PAGE_READWRITE,
					0,
					sizeForCreate,
					name);
				if (shareMemoryImpl->mFileMapHandle)
				{
					shareMemoryImpl->mCreateFlag = T_TRUE;
					shareMemoryImpl->mSize = sizeForCreate;
				}
			}

			if (shareMemoryImpl->mFileMapHandle)
			{
				shareMemoryImpl->mViewOfFile = MapViewOfFile(
					shareMemoryImpl->mFileMapHandle,
					FILE_MAP_READ | FILE_MAP_WRITE,
					0,
					0,
					0);
				if (shareMemoryImpl->mViewOfFile)
				{
					TStringCopyW(shareMemoryImpl->mName, name, 0);

					return (T_OBJECT)shareMemoryImpl;
				}
			}

			if (shareMemoryImpl->mFileMapHandle)
			{
				CloseHandle(shareMemoryImpl->mFileMapHandle);
				shareMemoryImpl->mFileMapHandle = 0;
			}

			TMemset(shareMemoryImpl, sizeof(T_SHARE_MEMORY), 0);
		}
	}

	return 0;
}

T_OBJECT TShareMemoryOpenA(
	const char * name,
	const int sizeForCreate)
{
	T_OBJECT shareMemory = 0;
	wchar_t * nameW = 0;

	if (name)
	{
		nameW = TStringA2W(name);
		if (nameW)
		{
			shareMemory = TShareMemoryOpenW(nameW, sizeForCreate);

			TFree(nameW);
			nameW = 0;
		}
	}

	return shareMemory;
}

void TShareMemoryClose(
	T_OBJECT shareMemory)
{
	T_SHARE_MEMORY * shareMemoryImpl = (T_SHARE_MEMORY *)shareMemory;
	if (shareMemoryImpl)
	{
		if (shareMemoryImpl->mViewOfFile)
		{
			UnmapViewOfFile(shareMemoryImpl->mViewOfFile);
			shareMemoryImpl->mViewOfFile = 0;
		}

		if (shareMemoryImpl->mFileMapHandle)
		{
			CloseHandle(shareMemoryImpl->mFileMapHandle);
			shareMemoryImpl->mFileMapHandle = 0;
		}

		TMemset(shareMemoryImpl, sizeof(T_SHARE_MEMORY), 0);
	}
}

int TShareMemoryWrite(
	T_OBJECT shareMemory,
	const void * data,
	const int offset,
	const int bytesToWrite)
{
	unsigned char * viewOfFile = 0;

	T_SHARE_MEMORY * shareMemoryImpl = (T_SHARE_MEMORY *)shareMemory;
	if (shareMemoryImpl && shareMemoryImpl->mViewOfFile && data && bytesToWrite)
	{
		viewOfFile = (unsigned char *)shareMemoryImpl->mViewOfFile;
		memcpy(&(viewOfFile[offset]), data, bytesToWrite);

		return T_TRUE;
	}

	return T_FALSE;
}

int TShareMemoryRead(
	T_OBJECT shareMemory,
	void * data,
	const int offset,
	const int bytesToRead)
{
	unsigned char * viewOfFile = 0;

	T_SHARE_MEMORY * shareMemoryImpl = (T_SHARE_MEMORY *)shareMemory;
	if (shareMemoryImpl && shareMemoryImpl->mViewOfFile && data && bytesToRead)
	{
		viewOfFile = (unsigned char *)shareMemoryImpl->mViewOfFile;
		memcpy(data, &(viewOfFile[offset]), bytesToRead);

		return T_TRUE;
	}

	return T_FALSE;
}

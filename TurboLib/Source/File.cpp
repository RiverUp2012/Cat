
#include "../TurboLib.h"
#include "../Include/Private.h"

#define T_MAX_FILE_NAME (260)
#define T_MAX_FILE (64)

typedef struct _T_FILE
{
	HANDLE mFileHandle;
	int mForRead;
	int mForWrite;
}
T_FILE;

static T_FILE gFileArray[T_MAX_FILE] = { 0 };

static T_FILE * TFindUnuseFile(void)
{
	for (int i = 0; i < T_MAX_FILE; ++i)
	{
		if (!gFileArray[i].mFileHandle)
		{
			return &gFileArray[i];
		}
	}

	return 0;
}

T_OBJECT TFileOpenW(
	const wchar_t * fileName,
	const int forRead,
	const int forWrite)
{
	DWORD desiredAccess = 0;
	DWORD creationDisposition = 0;
	DWORD lastError = 0;

	if (fileName)
	{
		T_FILE * fileImpl = TFindUnuseFile();
		if (fileImpl)
		{
			fileImpl->mForRead = forRead;
			fileImpl->mForWrite = forWrite;

			if (forRead && forWrite)
			{
				desiredAccess = GENERIC_READ | GENERIC_WRITE;
				creationDisposition = CREATE_NEW;
			}
			else if (forRead)
			{
				desiredAccess = GENERIC_READ;
				creationDisposition = OPEN_ALWAYS;
			}
			else if (forWrite)
			{
				desiredAccess = GENERIC_WRITE;
				creationDisposition = CREATE_NEW;
			}

			fileImpl->mFileHandle = CreateFileW(
				fileName,
				desiredAccess,
				0,
				0,
				creationDisposition,
				0,
				0);
			if (INVALID_HANDLE_VALUE == fileImpl->mFileHandle)
			{
				lastError = GetLastError();

				if (forRead && forWrite)
				{

				}
				else if (forRead)
				{

				}
				else if (forWrite)
				{

				}
			}

			if (INVALID_HANDLE_VALUE == fileImpl->mFileHandle)
			{
				TMemset(fileImpl, sizeof(T_FILE), 0);
				fileImpl = 0;
			}

			return (T_OBJECT)fileImpl;
		}
	}

	return 0;
}

T_OBJECT TFileOpenA(
	const char * fileName,
	const int forRead,
	const int forWrite)
{
	DWORD desiredAccess = 0;
	DWORD creationDisposition = 0;
	DWORD lastError = 0;

	if (fileName)
	{
		T_FILE * fileImpl = TFindUnuseFile();
		if (fileImpl)
		{
			fileImpl->mForRead = forRead;
			fileImpl->mForWrite = forWrite;

			if (forRead && forWrite)
			{
				desiredAccess = GENERIC_READ | GENERIC_WRITE;
				creationDisposition = CREATE_NEW;
			}
			else if (forRead)
			{
				desiredAccess = GENERIC_WRITE;
				creationDisposition = OPEN_ALWAYS;
			}
			else if (forWrite)
			{
				desiredAccess = GENERIC_READ;
				creationDisposition = CREATE_NEW;
			}

			fileImpl->mFileHandle = CreateFileA(
				fileName,
				desiredAccess,
				0,
				0,
				creationDisposition,
				0,
				0);
			if (INVALID_HANDLE_VALUE == fileImpl->mFileHandle)
			{
				lastError = GetLastError();

				if (forRead && forWrite)
				{

				}
				else if (forRead)
				{

				}
				else if (forWrite)
				{

				}
			}

			if (INVALID_HANDLE_VALUE == fileImpl->mFileHandle)
			{
				TMemset(fileImpl, sizeof(T_FILE), 0);
				fileImpl = 0;
			}

			return (T_OBJECT)fileImpl;
		}
	}

	return 0;
}

void TFileClose(
	T_OBJECT file)
{
	T_FILE * fileImpl = (T_FILE *)file;
	if (fileImpl)
	{
		if (INVALID_HANDLE_VALUE != fileImpl->mFileHandle)
		{
			CloseHandle(fileImpl->mFileHandle);
			fileImpl->mFileHandle = 0;
		}

		TMemset(fileImpl, sizeof(T_FILE), 0);
	}
}

int TFileGetSize(
	T_OBJECT file,
	long long int * fileSize)
{
	LARGE_INTEGER fileSizeTemp = { 0 };

	T_FILE * fileImpl = (T_FILE *)file;
	if (fileImpl &&
		INVALID_HANDLE_VALUE != fileImpl->mFileHandle &&
		fileSize)
	{
		if (GetFileSizeEx(fileImpl->mFileHandle, &fileSizeTemp))
		{
			*fileSize = fileSizeTemp.QuadPart;

			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TFileRead(
	T_OBJECT file,
	void * buffer,
	const int bytesToRead)
{
	DWORD bytesReaded = 0;

	T_FILE * fileImpl = (T_FILE *)file;
	if (fileImpl &&
		INVALID_HANDLE_VALUE != fileImpl->mFileHandle &&
		fileImpl->mForRead &&
		buffer &&
		bytesToRead > 0)
	{
		if (ReadFile(fileImpl->mFileHandle, buffer, bytesToRead, &bytesReaded, 0))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TFileWrite(
	T_OBJECT file,
	const void * buffer,
	const int bytesToWrite)
{
	DWORD bytesWrited = 0;

	T_FILE * fileImpl = (T_FILE *)file;
	if (fileImpl &&
		INVALID_HANDLE_VALUE != fileImpl->mFileHandle &&
		fileImpl->mForWrite &&
		buffer &&
		bytesToWrite > 0)
	{
		if (WriteFile(fileImpl->mFileHandle, buffer, bytesToWrite, &bytesWrited, 0))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TFileSeekTo(
	T_OBJECT file,
	const long long int toPos)
{
	LARGE_INTEGER toPosTemp = { 0 };
	LARGE_INTEGER newPos = { 0 };

	T_FILE * fileImpl = (T_FILE *)file;
	if (fileImpl && INVALID_HANDLE_VALUE != fileImpl->mFileHandle)
	{
		toPosTemp.QuadPart = toPos;

		if (SetFilePointerEx(fileImpl->mFileHandle, toPosTemp, &newPos, FILE_BEGIN))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TFileSeekToBegin(
	T_OBJECT file)
{
	LARGE_INTEGER toPosTemp = { 0 };
	LARGE_INTEGER newPos = { 0 };

	T_FILE * fileImpl = (T_FILE *)file;
	if (fileImpl && INVALID_HANDLE_VALUE != fileImpl->mFileHandle)
	{
		toPosTemp.QuadPart = 0;

		if (SetFilePointerEx(fileImpl->mFileHandle, toPosTemp, &newPos, FILE_BEGIN))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TFileSeekToEnd(
	T_OBJECT file)
{
	LARGE_INTEGER toPosTemp = { 0 };
	LARGE_INTEGER newPos = { 0 };

	T_FILE * fileImpl = (T_FILE *)file;
	if (fileImpl && INVALID_HANDLE_VALUE != fileImpl->mFileHandle)
	{
		toPosTemp.QuadPart = 0;

		if (SetFilePointerEx(fileImpl->mFileHandle, toPosTemp, &newPos, FILE_END))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TFileSeekOffset(
	T_OBJECT file,
	const long long int offset)
{
	LARGE_INTEGER offsetTemp = { 0 };
	LARGE_INTEGER newPos = { 0 };

	T_FILE * fileImpl = (T_FILE *)file;
	if (fileImpl && INVALID_HANDLE_VALUE != fileImpl->mFileHandle)
	{
		offsetTemp.QuadPart = offset;

		if (SetFilePointerEx(fileImpl->mFileHandle, offsetTemp, &newPos, FILE_CURRENT))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TFileGetPointer(
	T_OBJECT file,
	long long int * pointer)
{
	LARGE_INTEGER toPosTemp = { 0 };
	LARGE_INTEGER newPos = { 0 };

	T_FILE * fileImpl = (T_FILE *)file;
	if (fileImpl && INVALID_HANDLE_VALUE != fileImpl->mFileHandle && pointer)
	{
		toPosTemp.QuadPart = 0;

		if (SetFilePointerEx(fileImpl->mFileHandle, toPosTemp, &newPos, FILE_CURRENT))
		{
			*pointer = newPos.QuadPart;

			return T_TRUE;
		}
	}

	return T_FALSE;
}

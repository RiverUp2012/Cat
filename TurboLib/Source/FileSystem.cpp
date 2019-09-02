
#include "../TurboLib.h"
#include "../Include/Private.h"

int TFileSystemDeleteFileW(
	const wchar_t * fileName)
{
	DWORD fileAttributes = 0;

	if (fileName)
	{
		fileAttributes = GetFileAttributesW(fileName);
		if (INVALID_FILE_ATTRIBUTES != fileAttributes)
		{
			if (fileAttributes & FILE_ATTRIBUTE_READONLY)
			{
				fileAttributes &= ~FILE_ATTRIBUTE_READONLY;
				if (!SetFileAttributesW(fileName, fileAttributes))
				{
					return T_FALSE;
				}
			}

			if (DeleteFileW(fileName))
			{
				return T_TRUE;
			}
		}
	}

	return T_FALSE;
}

int TFileSystemDeleteFileA(
	const char * fileName)
{
	DWORD fileAttributes = 0;

	if (fileName)
	{
		fileAttributes = GetFileAttributesA(fileName);
		if (INVALID_FILE_ATTRIBUTES != fileAttributes)
		{
			if (fileAttributes & FILE_ATTRIBUTE_READONLY)
			{
				fileAttributes &= ~FILE_ATTRIBUTE_READONLY;
				if (!SetFileAttributesA(fileName, fileAttributes))
				{
					return T_FALSE;
				}
			}

			if (DeleteFileA(fileName))
			{
				return T_TRUE;
			}
		}
	}

	return T_FALSE;
}

void TFileSystemEnumFileW(
	const wchar_t * path,
	const wchar_t * fileExt,
	TEnumFileCallbackProcW enumFileProc,
	void * userData)
{
	int pathLength = path ? TStringLengthW(path) : 0;
	int fileExtLength = fileExt ? TStringLengthW(fileExt) : 0;
	wchar_t * pathTemp = 0;
	WIN32_FIND_DATAW findData = { 0 };
	HANDLE findHandle = INVALID_HANDLE_VALUE;
	int isDirectory = T_FALSE;

	if (path && fileExt && pathLength > 0 && fileExtLength > 0 && enumFileProc)
	{
		pathTemp = TStringAllocW(pathLength + fileExtLength + 2);
		if (pathTemp)
		{
			TStringCopyW(pathTemp, path, pathLength);
			TFilePathAppendW(pathTemp, fileExt);

			findHandle = FindFirstFileW(pathTemp, &findData);
			if (INVALID_HANDLE_VALUE != findHandle)
			{
				do 
				{
					if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						if (L'.' == findData.cFileName[0])
						{
							continue;
						}

						isDirectory = T_TRUE;
					}
					else
					{
						isDirectory = T_FALSE;
					}

					if (!enumFileProc(path, findData.cFileName, isDirectory, userData))
					{
						break;
					}

				} while (FindNextFileW(findHandle, &findData));

				FindClose(findHandle);
				findHandle = 0;
			}

			TFree(pathTemp);
			pathTemp = 0;
		}
	}
}

void TFileSystemEnumFileA(
	const char * path,
	const char * fileExt,
	TEnumFileCallbackProcA enumFileProc,
	void * userData)
{
	int pathLength = path ? TStringLengthA(path) : 0;
	int fileExtLength = fileExt ? TStringLengthA(fileExt) : 0;
	char * pathTemp = 0;
	WIN32_FIND_DATAA findData = { 0 };
	HANDLE findHandle = INVALID_HANDLE_VALUE;
	int isDirectory = T_FALSE;

	if (path && fileExt && pathLength > 0 && fileExtLength > 0 && enumFileProc)
	{
		pathTemp = TStringAllocA(pathLength + fileExtLength + 2);
		if (pathTemp)
		{
			TStringCopyA(pathTemp, path, pathLength);
			TFilePathAppendA(pathTemp, fileExt);

			findHandle = FindFirstFileA(pathTemp, &findData);
			if (INVALID_HANDLE_VALUE != findHandle)
			{
				do
				{
					if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						if ('.' == findData.cFileName[0])
						{
							continue;
						}

						isDirectory = T_TRUE;
					}
					else
					{
						isDirectory = T_FALSE;
					}

					if (!enumFileProc(path, findData.cFileName, isDirectory, userData))
					{
						break;
					}

				} while (FindNextFileA(findHandle, &findData));

				FindClose(findHandle);
				findHandle = 0;
			}

			TFree(pathTemp);
			pathTemp = 0;
		}
	}
}

int TFileSystemIsFileExistW(
	const wchar_t * fileName)
{
	if (fileName)
	{
		if (INVALID_FILE_ATTRIBUTES != GetFileAttributesW(fileName))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TFileSystemIsFileExistA(
	const char * fileName)
{
	if (fileName)
	{
		if (INVALID_FILE_ATTRIBUTES != GetFileAttributesA(fileName))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TFileSystemIsPathDirectoryW(
	const wchar_t * path)
{
	DWORD fileAttributes = 0;

	if (path)
	{
		fileAttributes = GetFileAttributesW(path);
		if (INVALID_FILE_ATTRIBUTES != fileAttributes)
		{
			if (fileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				return T_TRUE;
			}
		}
	}

	return T_FALSE;
}

int TFileSystemIsPathDirectoryA(
	const char * path)
{
	DWORD fileAttributes = 0;

	if (path)
	{
		fileAttributes = GetFileAttributesA(path);
		if (INVALID_FILE_ATTRIBUTES != fileAttributes)
		{
			if (fileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				return T_TRUE;
			}
		}
	}

	return T_FALSE;
}

void TFileSystemCreateDirectoryW(
	const wchar_t * directory)
{
	int directoryLength = directory ? TStringLengthW(directory) : 0;
	wchar_t * directoryTemp = 0;

	if (directory && directoryLength > 0)
	{
		directoryTemp = TStringAllocW(directoryLength + 1);
		if (directoryTemp)
		{
			for (int i = 0; i < directoryLength; ++i)
			{
				directoryTemp[i] = directory[i];

				if (L'\\' == directoryTemp[i] || L'/' == directoryTemp[i])
				{
					directoryTemp[i + 1] = L'\0';

					CreateDirectoryW(directoryTemp, 0);
				}
			}

			TFree(directoryTemp);
			directoryTemp = 0;
		}
	}
}

void TFileSystemCreateDirectoryA(
	const char * directory)
{
	int directoryLength = directory ? TStringLengthA(directory) : 0;
	char * directoryTemp = 0;

	if (directory && directoryLength > 0)
	{
		directoryTemp = TStringAllocA(directoryLength + 1);
		if (directoryTemp)
		{
			for (int i = 0; i < directoryLength; ++i)
			{
				directoryTemp[i] = directory[i];

				if ('\\' == directoryTemp[i] || '/' == directoryTemp[i])
				{
					directoryTemp[i + 1] = '\0';

					CreateDirectoryA(directoryTemp, 0);
				}
			}

			TFree(directoryTemp);
			directoryTemp = 0;
		}
	}
}

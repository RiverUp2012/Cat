
#include "../GameLibInclude/glFile.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glString.h"
#include "../GameLibInclude/glStringHelper.h"

glFile::glFile() {
	mFileHandle = 0;
	mMappingHandle = 0;
	mForRead = false;
	mForWrite = false;
	mView = 0;
}

glFile::~glFile() {
	close();
}

bool glFile::openW(
	const wchar_t * fileName,
	const bool forRead,
	const bool forWrite) {
	DWORD desiredAccess = 0;
	DWORD creationDisposition = 0;
	DWORD lastError = 0;
	LARGE_INTEGER fileSize = { 0 };
	close();
	if (fileName) {
		if (forRead && forWrite) {
			desiredAccess = GENERIC_READ | GENERIC_WRITE;
			creationDisposition = CREATE_NEW;
		}
		else if (forRead) {
			desiredAccess = GENERIC_READ;
			creationDisposition = OPEN_EXISTING;
		}
		else if (forWrite) {
			desiredAccess = GENERIC_WRITE;
			creationDisposition = CREATE_NEW;
		}
		mFileHandle = (void *)CreateFileW(
			fileName,
			desiredAccess,
			0,
			0,
			creationDisposition,
			0,
			0);
		if (INVALID_HANDLE_VALUE == (HANDLE)mFileHandle) {
			lastError = GetLastError();
			if (forRead && forWrite) {
				if (ERROR_FILE_EXISTS == lastError) {
					// 如果以 CREATE_NEW 标志打开一个已经存在的文件，并且打开失败时，
					// 尝试使用 OPEN_ALWAYS 标志再次打开
					creationDisposition = OPEN_ALWAYS;
				}
				else {
					throw glWin32APIException(L"CreateFileW", lastError);
				}
			}
			else if (forRead) {
				if (ERROR_FILE_NOT_FOUND == lastError) {
					// 如果尝试以只读的模式打开一个不存在的文件，打开必然失败，但不属于异常
					return false;
				}
				else {
					throw glWin32APIException(L"CreateFileW", lastError);
				}
			}
			else if (forWrite) {
				if (ERROR_FILE_EXISTS == lastError) {
					// 如果以 CREATE_NEW 标志打开一个已经存在的文件，并且打开失败时，
					// 尝试使用 OPEN_ALWAYS 标志再次打开
					creationDisposition = OPEN_ALWAYS;
				}
				else {
					throw glWin32APIException(L"CreateFileW", lastError);
				}
			}
			mFileHandle = (void *)CreateFileW(
				fileName,
				desiredAccess,
				0,
				0,
				creationDisposition,
				0,
				0);
		}
		if (INVALID_HANDLE_VALUE != (HANDLE)mFileHandle) {
			if (forRead && !forWrite) {
				// 对于以只读模式打开的文件，尝试使用文件映射的方式来优化文件读取性能
				mMappingHandle = (void *)CreateFileMappingW(
					(HANDLE)mFileHandle,
					0,
					PAGE_READONLY,
					0,
					0,
					0);
				if (mMappingHandle) {
					mView = (unsigned char *)MapViewOfFile(
						(HANDLE)mMappingHandle,
						FILE_MAP_READ,
						0,
						0,
						0);
					if (mView) {
						return true;
					}
					else {
						throw glWin32APIException(L"MapViewOfFile", GetLastError());
					}
				}
				else {
					lastError = GetLastError();
					if (GetFileSizeEx((HANDLE)mFileHandle, &fileSize)) {
						if (0 == fileSize.QuadPart) {
							// 对于以只读模式打开的文件，若文件大小为 0 时，创建文件映射必然失败，但不属于异常
							return false;
						}
						else {
							throw glWin32APIException(L"CreateFileMappingW", lastError);
						}
					}
					else {
						throw glWin32APIException(L"GetFileSizeEx", GetLastError());
					}
				}
			}
			else {
				return true;
			}
		}
		else {
			throw glWin32APIException(L"CreateFileW", GetLastError());
		}
	}
	return false;
}

bool glFile::openA(
	const char * fileName,
	const bool forRead,
	const bool forWrite) {
	glStringW fileNameW;
	if (glStringHelper::a2w(fileName, fileNameW)) {
		return openW(fileNameW, forRead, forWrite);
	}
	return false;
}

void glFile::close(void) {
	if (mView) {
		UnmapViewOfFile(mView);
		mView = 0;
	}
	if (mMappingHandle) {
		CloseHandle((HANDLE)mMappingHandle);
		mMappingHandle = 0;
	}
	if (mFileHandle) {
		CloseHandle((HANDLE)mFileHandle);
		mFileHandle = 0;
	}
	mForRead = false;
	mForWrite = false;
}

bool glFile::isAlready(void) const {
	return mFileHandle ? true : false;
}

bool glFile::isEndOfFile(bool & endOfFile) {
	LARGE_INTEGER fileSize = { 0 };
	LARGE_INTEGER toPos = { 0 };
	LARGE_INTEGER newPos = { 0 };
	if (mFileHandle) {
		if (GetFileSizeEx((HANDLE)mFileHandle, &fileSize)) {
			if (SetFilePointerEx((HANDLE)mFileHandle, toPos, &newPos, FILE_CURRENT)) {
				if (newPos.QuadPart >= fileSize.QuadPart) {
					endOfFile = true;
				}
				return true;
			}
			else {
				throw glWin32APIException(L"SetFilePointerEx", GetLastError());
			}
		}
		else {
			throw glWin32APIException(L"GetFileSizeEx", GetLastError());
		}
	}
	return false;
}

bool glFile::isForRead(void) const {
	return mForRead;
}

bool glFile::isForWrite(void) const {
	return mForWrite;
}

bool glFile::seekToBegin(void) {
	LARGE_INTEGER toPos = { 0 };
	LARGE_INTEGER newPos = { 0 };
	if (mFileHandle) {
		if (SetFilePointerEx((HANDLE)mFileHandle, toPos, &newPos, FILE_BEGIN)) {
			return true;
		}
		else {
			throw glWin32APIException(L"SetFilePointerEx", GetLastError());
		}
	}
	return false;
}

bool glFile::seekToEnd(void) {
	LARGE_INTEGER toPos = { 0 };
	LARGE_INTEGER newPos = { 0 };
	if (mFileHandle) {
		if (SetFilePointerEx((HANDLE)mFileHandle, toPos, &newPos, FILE_END)) {
			return true;
		}
		else {
			throw glWin32APIException(L"SetFilePointerEx", GetLastError());
		}
	}
	return false;
}

bool glFile::seekTo(const long long int pos) {
	LARGE_INTEGER toPos = { 0 };
	LARGE_INTEGER newPos = { 0 };
	if (mFileHandle) {
		toPos.QuadPart = pos;
		if (SetFilePointerEx((HANDLE)mFileHandle, toPos, &newPos, FILE_BEGIN)) {
			return true;
		}
		else {
			throw glWin32APIException(L"SetFilePointerEx", GetLastError());
		}
	}
	return false;
}

bool glFile::seekOffset(const long long int offset) {
	LARGE_INTEGER offsetTemp = { 0 };
	LARGE_INTEGER newPos = { 0 };
	if (mFileHandle) {
		offsetTemp.QuadPart = offset;
		if (SetFilePointerEx((HANDLE)mFileHandle, offsetTemp, &newPos, FILE_CURRENT)) {
			return true;
		}
		else {
			throw glWin32APIException(L"SetFilePointerEx", GetLastError());
		}
	}
	return false;
}

bool glFile::getPointer(long long int & pointer) {
	LARGE_INTEGER offset = { 0 };
	LARGE_INTEGER newPos = { 0 };
	if (mFileHandle) {
		if (SetFilePointerEx((HANDLE)mFileHandle, offset, &newPos, FILE_CURRENT)) {
			pointer = newPos.QuadPart;
			return true;
		}
		else {
			throw glWin32APIException(L"SetFilePointerEx", GetLastError());
		}
	}
	return false;
}

bool glFile::getFileSize(long long int & fileSize) {
	LARGE_INTEGER fileSizeTemp = { 0 };
	if (mFileHandle) {
		if (GetFileSizeEx((HANDLE)mFileHandle, &fileSizeTemp)) {
			fileSize = fileSizeTemp.QuadPart;
			return true;
		}
		else {
			throw glWin32APIException(L"GetFileSizeEx", GetLastError());
		}
	}
	return false;
}

bool glFile::write(const void * data, const int bytesToWrite) {
	DWORD bytesWrited = 0;
	if (mFileHandle && data && bytesToWrite > 0) {
		if (WriteFile((HANDLE)mFileHandle, data, bytesToWrite, &bytesWrited, 0)) {
			return true;
		}
		else {
			throw glWin32APIException(L"WriteFile", GetLastError());
		}
	}
	return false;
}

bool glFile::read(void * data, const int bytesToRead) {
	DWORD bytesReaded = 0;
	if (mFileHandle && data && bytesToRead > 0) {
		if (ReadFile((HANDLE)mFileHandle, data, bytesToRead, &bytesReaded, 0)) {
			return true;
		}
		else {
			throw glWin32APIException(L"ReadFile", GetLastError());
		}
	}
	return false;
}

const unsigned char * glFile::getViewPointer(void) const {
	return mView;
}


#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

glFile::glFile() {
	mFileHandle = 0;
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
	close();
	if (fileName) {
		if (forRead && forWrite) {
			desiredAccess = GENERIC_READ | GENERIC_WRITE;
			creationDisposition = CREATE_NEW;
		}
		else if (forRead) {
			desiredAccess = GENERIC_READ;
			creationDisposition = OPEN_ALWAYS;
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

			}
			else if (forRead) {

			}
			else if (forWrite) {

			}
		}
		else {
			return true;
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
	if (mFileHandle) {
		CloseHandle((HANDLE)mFileHandle);
		mFileHandle = 0;
	}
}

bool glFile::isAlready(void) const {
	return mFileHandle ? true : false;
}

bool glFile::seekToBegin(void) {
	LARGE_INTEGER toPos = { 0 };
	LARGE_INTEGER newPos = { 0 };
	if (mFileHandle) {
		if (SetFilePointerEx((HANDLE)mFileHandle, toPos, &newPos, FILE_BEGIN)) {
			return true;
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
	}
	return false;
}

bool glFile::write(const void * data, const int bytesToWrite) {
	DWORD bytesWrited = 0;
	if (mFileHandle && data && bytesToWrite > 0) {
		if (WriteFile((HANDLE)mFileHandle, data, bytesToWrite, &bytesWrited, 0)) {
			return true;
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
	}
	return false;
}


#include "../GameLibInclude/glFileHelper.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glPathHelper.h"
#include "../GameLibInclude/glFileEnumHandler.h"

bool glFileHelper::deleteFileW(const wchar_t * fileName) {
	DWORD fileAttributes = 0;
	if (fileName) {
		fileAttributes = GetFileAttributesW(fileName);
		if (INVALID_FILE_ATTRIBUTES != fileAttributes) {
			if (fileAttributes & FILE_ATTRIBUTE_READONLY) {
				fileAttributes &= ~FILE_ATTRIBUTE_READONLY;
				if (!SetFileAttributesW(fileName, fileAttributes)) {
					throw glWin32APIException(L"SetFileAttributesW", GetLastError());
				}
			}
			if (DeleteFileW(fileName)) {
				return true;
			}
			else {
				throw glWin32APIException(L"DeleteFileW", GetLastError());
			}
		}
	}
	return false;
}

void glFileHelper::enumFileW(
	const wchar_t * path,
	const wchar_t * fileExt,
	glFileEnumHandler * enumHandler) {
	WIN32_FIND_DATAW wfd = { 0 };
	HANDLE findHandle = INVALID_HANDLE_VALUE;
	glStringW pathForFind;
	glStringW pathForFindWithFileExt;
	bool isDirectory = false;
	if (path && fileExt && enumHandler) {
		pathForFind = path;
		glPathHelper::pathAppendSlashW(pathForFind);
		pathForFindWithFileExt = pathForFind + fileExt;
		findHandle = FindFirstFileW(pathForFindWithFileExt, &wfd);
		if (INVALID_HANDLE_VALUE != findHandle) {
			do {
				isDirectory = false;
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					if (L'.' == wfd.cFileName[0]) {
						continue;
					}
					isDirectory = true;
				}
				if (!enumHandler->onFileEnumW(pathForFind, wfd.cFileName, isDirectory)) {
					break;
				}
			} while (FindNextFileW(findHandle, &wfd));
			FindClose(findHandle);
			findHandle = INVALID_HANDLE_VALUE;
		}
	}
}

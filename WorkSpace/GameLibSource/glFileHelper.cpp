
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

bool glFileHelper::deleteFileW(const wchar_t * fileName) {
	DWORD fileAttributes = 0;
	if (fileName) {
		fileAttributes = GetFileAttributesW(fileName);
		if (INVALID_FILE_ATTRIBUTES != fileAttributes) {
			if (fileAttributes & FILE_ATTRIBUTE_READONLY) {
				fileAttributes &= ~FILE_ATTRIBUTE_READONLY;
				if (!SetFileAttributesW(fileName, fileAttributes)) {
					return false;
				}
			}
			if (DeleteFileW(fileName)) {
				return true;
			}
		}
	}
	return false;
}


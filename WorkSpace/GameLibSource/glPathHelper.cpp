
#include "../GameLibInclude/glPathHelper.h"
#include "../GameLibInclude/glString.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glException.h"

bool glPathHelper::getFileNameWithExtW(const wchar_t * path, glStringW & fileNameWithExt) {
	int pathLength = path ? glStringW::getLength(path) : 0;
	if (path && pathLength > 0) {
		for (int i = pathLength - 1; i >= 0; --i) {
			if (L'\\' == path[i]) {
				if (fileNameWithExt.resize(i + 1)) {
					glStringW::copy(fileNameWithExt.getBuffer(), path, i);
					fileNameWithExt.setAt(i, L'\0');
					return true;
				}
				break;
			}
		}
	}
	return false;
}

bool glPathHelper::getDriveW(const wchar_t * path, glStringW & drive) {
	const int pathLength = path ? glStringW::getLength(path) : 0;
	if (path && pathLength > 2 && drive.resize(4)) {
		if ((path[0] >= L'A' && path[0] <= L'Z') ||
			(path[0] >= L'a' && path[0] <= L'z')) {
			if (L':' == path[1]) {
				if (2 == pathLength) {
					glStringW::copy(drive.getBuffer(), path, 2);
					drive.setAt(2, L'\0');
					return true;
				}
				else if (L'\\' == path[2] || L'/' == path[2]) {
					glStringW::copy(drive.getBuffer(), path, 3);
					drive.setAt(3, L'\0');
					return true;
				}
			}
		}
	}
	return false;
}

bool glPathHelper::getAppPathW(glStringW & appPath) {
	wchar_t appPathTemp[520] = { 0 };
	if (GetModuleFileNameW(0, appPathTemp, _countof(appPathTemp))) {
		for (int i = glStringW::getLength(appPathTemp) - 1; i >= 0; --i) {
			if (L'\\' == appPathTemp[i]) {
				appPathTemp[i + 1] = L'\0';
				appPath = appPathTemp;
				return true;
			}
		}
	}
	return false;
}

void glPathHelper::pathAppendSlashW(glStringW & path) {
	const int pathLength = path.getLength();
	if (pathLength > 0) {
		const wchar_t & lastChar = path.getAt(pathLength - 1);
		if (L'\\' != lastChar && L'/' != lastChar) {
			path += L"\\";
		}
	}
}

void glPathHelper::createPathW(const wchar_t * path) {
	const int pathLength = path ? glStringW::getLength(path) : 0;
	glStringW pathTemp;
	if (path && pathLength > 0 && pathTemp.resize(pathLength + 1)) {
		for (int i = 0; i < pathLength; ++i) {
			pathTemp.setAt(i, path[i]);
			if (L'\\' == path[i] || L'/' == path[i]) {
				pathTemp.setAt(i + 1, L'\0');
				if (0 == CreateDirectoryW(pathTemp, 0)) {
					const DWORD lastError = GetLastError();
					if (ERROR_ALREADY_EXISTS != lastError) {
						throw glWin32APIException(L"CreateDirectoryW", lastError);
					}
				}
			}
		}
	}
}


#include "../WinLib.h"
#include "../Include/WinLibPrivate.h"

bool wlPathHelper::getFileNameWithExtW(const wchar_t * path, glStringW & fileNameWithExt) {
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

bool wlPathHelper::getAppPathW(glStringW & appPath) {
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

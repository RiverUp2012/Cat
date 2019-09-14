
#include "../WinLib.h"
#include <string>

bool wlPathHelper::getFileNameWithExtW(const wchar_t * path, sgeStringW & fileNameWithExt) {
	const std::wstring pathTemp = path ? path : L"";
	const std::wstring::size_type findIndex = pathTemp.find_last_of(L'\\');
	if (std::wstring::npos != findIndex) {
		fileNameWithExt = pathTemp.substr(findIndex + 1).c_str();
		return true;
	}
	return false;
}

bool wlPathHelper::getAppPathW(sgeStringW & appPath) {
	wchar_t appPathTemp[520] = { 0 };
	if (GetModuleFileNameW(0, appPathTemp, _countof(appPathTemp))) {
		for (int i = wcslen(appPathTemp) - 1; i >= 0; --i) {
			if (L'\\' == appPathTemp[i]) {
				appPathTemp[i + 1] = L'\0';
				appPath = appPathTemp;
				return true;
			}
		}
	}
	return false;
}

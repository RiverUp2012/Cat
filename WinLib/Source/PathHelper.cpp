
#include "../Include/WinLib.h"

namespace wl {

	bool PathHelper::getFileNameWithExtW(const wchar_t * path, std::wstring & fileNameWithExt) {
		const std::wstring pathTemp = path ? path : L"";
		const std::wstring::size_type findIndex = pathTemp.find_last_of(L'\\');
		if (std::wstring::npos != findIndex) {
			fileNameWithExt = pathTemp.substr(findIndex + 1);
			return true;
		}
		return false;
	}

	bool PathHelper::getAppPathW(std::wstring & appPath) {
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

} // namespace wl

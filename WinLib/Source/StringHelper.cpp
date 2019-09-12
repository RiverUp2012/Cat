
#include "../Include/WinLib.h"

namespace wl {

	bool StringHelper::a2w(const char * stringA, std::wstring & stringW, const bool toUTF8) {
		size_t stringALength = 0;
		int stringWLength = 0;
		if (stringA) {
			stringALength = strlen(stringA);
			if (stringALength > 0) {
				stringWLength = MultiByteToWideChar(
					toUTF8 ? CP_UTF8 : CP_ACP,
					0,
					stringA,
					stringALength,
					0,
					0);
				if (stringWLength > 0) {
					stringW.resize(stringWLength + 1);
					if (MultiByteToWideChar(
						toUTF8 ? CP_UTF8 : CP_ACP,
						0,
						stringA,
						stringALength,
						&stringW[0],
						stringW.capacity())) {
						stringW[stringWLength] = L'\0';
						return true;
					}
				}
			}
		}
		return false;
	}

	bool StringHelper::w2a(const wchar_t * stringW, std::string & stringA, const bool toUTF8) {
		size_t stringWLength = 0;
		int stringALength = 0;
		if (stringW) {
			stringWLength = wcslen(stringW);
			if (stringWLength > 0) {
				stringALength = WideCharToMultiByte(
					toUTF8 ? CP_UTF8 : CP_ACP,
					0,
					stringW,
					stringWLength,
					0,
					0,
					0,
					0);
				if (stringALength > 0) {
					stringA.resize(stringALength + 1);
					if (WideCharToMultiByte(
						toUTF8 ? CP_UTF8 : CP_ACP,
						0,
						stringW,
						stringWLength,
						&stringA[0],
						stringA.capacity(),
						0,
						0)) {
						stringA[stringALength] = '\0';
						return true;
					}
				}
			}
		}
		return false;
	}

} // namespace wl

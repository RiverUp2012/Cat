
#include "../WinLib.h"
#include "../Include/WinLibPrivate.h"

bool wlStringHelper::a2w(const char * stringA, glStringW & stringW, const bool toUTF8) {
	int stringALength = 0;
	int stringWLength = 0;
	if (stringA) {
		stringALength = glStringA::getLength(stringA);
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
					stringW.getBuffer(),
					stringW.getCapacity())) {
					stringW.setAt(stringWLength, L'\0');
					return true;
				}
			}
		}
	}
	return false;
}

bool wlStringHelper::w2a(const wchar_t * stringW, glStringA & stringA, const bool toUTF8) {
	int stringWLength = 0;
	int stringALength = 0;
	if (stringW) {
		stringWLength = glStringW::getLength(stringW);
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
					stringA.getBuffer(),
					stringA.getCapacity(),
					0,
					0)) {
					stringA.setAt(stringALength, '\0');
					return true;
				}
			}
		}
	}
	return false;
}

bool wlStringHelper::formatW(const wchar_t * format, const va_list & vl, glStringW & string) {
	int stringLength = 0;
	if (format && vl) {
		stringLength = _vscwprintf(format, vl);
		if (stringLength > 0 && string.resize(stringLength + 1)) {
			vswprintf_s(string.getBuffer(), string.getCapacity(), format, vl);
			string.setAt(stringLength, L'\0');
			return true;
		}
	}
	return false;
}

bool wlStringHelper::formatA(const char * format, const va_list & vl, glStringA & string) {
	int stringLength = 0;
	if (format && vl) {
		stringLength = _vscprintf(format, vl);
		if (stringLength > 0 && string.resize(stringLength + 1)) {
			vsprintf_s(string.getBuffer(), string.getCapacity(), format, vl);
			string.setAt(stringLength, '\0');
			return true;
		}
	}
	return false;
}

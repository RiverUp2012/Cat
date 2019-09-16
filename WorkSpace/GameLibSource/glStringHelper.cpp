
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

bool glStringHelper::a2w(const char * stringA, glStringW & stringW, const bool toUTF8) {
	int stringALength = stringA ? glStringA::getLength(stringA) : 0;
	int stringWLength = 0;
	if (stringALength > 0) {
		stringWLength = MultiByteToWideChar(
			toUTF8 ? CP_UTF8 : CP_ACP,
			0,
			stringA,
			stringALength,
			0,
			0);
		if (stringWLength > 0 && stringW.resize(stringWLength + 1)) {
			MultiByteToWideChar(
				toUTF8 ? CP_UTF8 : CP_ACP,
				0,
				stringA,
				stringALength,
				stringW.getBuffer(),
				stringW.getCapacity());
			stringW.setAt(stringWLength, stringW.getNullChar());
			return true;
		}
	}
	return false;
}

bool glStringHelper::w2a(const wchar_t * stringW, glStringA & stringA, const bool toUTF8) {
	int stringALength = 0;
	int stringWLength = stringW ? glStringW::getLength(stringW) : 0;
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
		if (stringALength > 0 && stringA.resize(stringALength + 1)) {
			WideCharToMultiByte(
				toUTF8 ? CP_UTF8 : CP_ACP,
				0,
				stringW,
				stringWLength,
				stringA.getBuffer(),
				stringA.getCapacity(),
				0,
				0);
			stringA.setAt(stringALength, stringA.getNullChar());
			return true;
		}
	}
	return false;
}

int glStringHelper::findA(const char * string, const char * subString) {
	if (string && subString) {
		const char * findRet = strstr(string, subString);
		if (findRet) {
			return (int)string - (int)findRet;
		}
	}
	return -1;
}

int glStringHelper::findW(const wchar_t * string, const wchar_t * subString) {
	if (string && subString) {
		const wchar_t * findRet = wcsstr(string, subString);
		if (findRet) {
			return (int)findRet - (int)string;
		}
	}
	return -1;
}

bool glStringHelper::formatW(const wchar_t * format, const va_list & vl, glStringW & string) {
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

bool glStringHelper::formatA(const char * format, const va_list & vl, glStringA & string) {
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

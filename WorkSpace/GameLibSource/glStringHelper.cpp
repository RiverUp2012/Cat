
#include "../GameLibInclude/glStringHelper.h"
#include "../GameLibInclude/glString.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glPrivate.h"

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
		if (0 == stringWLength) {
			throw glWin32APIException(L"MultiByteToWideChar", GetLastError());
		}
		else if (stringWLength > 0 && stringW.resize(stringWLength + 1)) {
			if (0 == MultiByteToWideChar(
				toUTF8 ? CP_UTF8 : CP_ACP,
				0,
				stringA,
				stringALength,
				stringW.getBuffer(),
				stringW.getCapacity())) {
				throw glWin32APIException(L"MultiByteToWideChar", GetLastError());
			}
			else {
				stringW.setAt(stringWLength, stringW.getNullChar());
				return true;
			}
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
		if (0 == stringALength) {
			throw glWin32APIException(L"WideCharToMultiByte", GetLastError());
		}
		else if (stringALength > 0 && stringA.resize(stringALength + 1)) {
			if (0 == WideCharToMultiByte(
				toUTF8 ? CP_UTF8 : CP_ACP,
				0,
				stringW,
				stringWLength,
				stringA.getBuffer(),
				stringA.getCapacity(),
				0,
				0)) {
				throw glWin32APIException(L"WideCharToMultiByte", GetLastError());
			}
			else {
				stringA.setAt(stringALength, stringA.getNullChar());
				return true;
			}
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

bool glStringHelper::formatW(glStringW & string, const wchar_t * format, ...) {
	bool ret = false;
	va_list vl = { 0 };
	va_start(vl, format);
	ret = formatW(format, vl, string);
	va_end(vl);
	return ret;
}

bool glStringHelper::formatA(glStringA & string, const char * format, ...) {
	bool ret = false;
	va_list vl = { 0 };
	va_start(vl, format);
	ret = formatA(format, vl, string);
	va_end(vl);
	return ret;
}

int glStringHelper::toIntW(const wchar_t * string) {
	if (!string) {
		throw glException(L"invalid param");
	}
	return _wtoi(string);
}

int glStringHelper::toIntA(const char * string) {
	if (!string) {
		throw glException(L"invalid param");
	}
	return atoi(string);
}

bool glStringHelper::endWithNewLineW(const wchar_t * string) {
	const int stringLength = string ? glStringW::getLength(string) : 0;
	if (string && stringLength > 1) {
		if (L'\r' == string[stringLength - 2] &&
			L'\n' == string[stringLength - 1]) {
			return true;
		}
	}
	return false;
}

bool glStringHelper::endWithNewLineA(const char * string) {
	const int stringLength = string ? glStringA::getLength(string) : 0;
	if (string && stringLength > 1) {
		if ('\r' == string[stringLength - 2] &&
			'\n' == string[stringLength - 1]) {
			return true;
		}
	}
	return false;
}

bool glStringHelper::formatW(const wchar_t * format, const va_list & vl, glStringW & string) {
	int stringLength = 0;
	if (format && vl) {
		stringLength = _vscwprintf(format, vl);
		if (stringLength > 0 && string.resize(stringLength + 1)) {
			vswprintf_s(string.getBuffer(), string.getCapacity(), format, vl);
			string.setAt(stringLength, string.getNullChar());
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
			string.setAt(stringLength, string.getNullChar());
			return true;
		}
	}
	return false;
}

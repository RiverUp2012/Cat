
#pragma once

#include "glString.h"
#include <stdarg.h>

//
// @brief ×Ö·û´®ÖúÊÖÀà
//
class glStringHelper {
public:
	static bool a2w(const char * stringA, glStringW & stringW, const bool toUTF8 = false);
	static bool w2a(const wchar_t * stringW, glStringA & stringA, const bool toUTF8 = false);
	static int findA(const char * string, const char * subString);
	static int findW(const wchar_t * string, const wchar_t * subString);
	static bool formatW(glStringW & string, const wchar_t * format, ...);
	static bool formatA(glStringA & string, const char * format, ...);
	static bool formatW(const wchar_t * format, const va_list & vl, glStringW & string);
	static bool formatA(const char * format, const va_list & vl, glStringA & string);
	static int toIntW(const wchar_t * string);
	static int toIntA(const char * string);
};

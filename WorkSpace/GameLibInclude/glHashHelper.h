
#pragma once

//
// @brief ɢ��������
//
class glHashHelper {
public:
	static unsigned int hashElfA(const char * string, const int charsToHash);
	static unsigned int hashElfW(const wchar_t * string, const int charsToHash);
};


#pragma once

#include "glString.h"

//
// @brief √¸¡Ó––¿‡
//
class glCmdLine {
public:
	static bool getParamByIndexW(const int index, glStringW & param);
	static bool isParamExistW(const wchar_t * param, int * index);
	static bool getSwitchValueW(const wchar_t * switchName, glStringW & value);
};

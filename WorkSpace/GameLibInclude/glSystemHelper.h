
#pragma once

#include "glString.h"

struct glMemoryInfo;

//
// @brief ϵͳ������
//
class glSystemHelper {
public:
	static bool getCurrentUserNameW(glStringW & userName);
	static bool getSystemDirectoryW(glStringW & systemDir);
	static bool getWindowDirectoryW(glStringW & windowDir);
	static bool getComputerNameW(glStringW & computerName);
	static bool getMemoryInfo(glMemoryInfo & memoryInfo);
};

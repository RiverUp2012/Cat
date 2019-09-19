
#pragma once

#include "glString.h"

struct glMemoryInfo;

//
// @brief 系统助手类
//
class glSystemHelper {
public:
	static bool getCurrentUserNameW(glStringW & userName);
	static bool getSystemDirectoryW(glStringW & systemDir);
	static bool getWindowDirectoryW(glStringW & windowDir);
	static bool getComputerNameW(glStringW & computerName);
	static bool getMemoryInfo(glMemoryInfo & memoryInfo);
};

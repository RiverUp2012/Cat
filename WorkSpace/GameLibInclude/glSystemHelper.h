
#pragma once

#include "glString.h"

struct glMemoryInfo;

//
// @brief 系统助手类
//
class glSystemHelper {
public:
	//
	// @brief 获取当前登录用户名
	//
	static bool getCurrentUserNameW(glStringW & userName);
	//
	// @brief 获取系统目录路径
	//
	static bool getSystemDirectoryW(glStringW & systemDir);
	//
	// @brief 获取 Windows 目录路径
	//
	static bool getWindowDirectoryW(glStringW & windowDir);
	//
	// @brief 获取计算机名称
	//
	static bool getComputerNameW(glStringW & computerName);
	//
	// @brief 获取内存信息
	//
	static bool getMemoryInfo(glMemoryInfo & memoryInfo);
};

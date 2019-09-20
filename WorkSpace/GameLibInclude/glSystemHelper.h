
#pragma once

#include "glString.h"

struct glMemoryInfo;

//
// @brief 操作系统版本枚举体
//
enum
{
	GL_OSVER_FIRST,
	GL_OSVER_WIN2K,
	GL_OSVER_WINXP,
	GL_OSVER_WINXP_SP1,
	GL_OSVER_WINXP_SP2,
	GL_OSVER_WINXP_SP3,
	GL_OSVER_WINVISTA,
	GL_OSVER_WINVISTA_SP1,
	GL_OSVER_WINVISTA_SP2,
	GL_OSVER_WIN7,
	GL_OSVER_WIN7_SP1,
	GL_OSVER_WIN8,
	GL_OSVER_WIN81,
	GL_OSVER_WIN10,
};

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
	//
	// @brief 获取操作系统版本
	//
	static bool getOSVersion(int & osVer);
};

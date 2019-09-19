
#pragma once

#include "glString.h"

//
// @brief 命令行类
//
class glCmdLine {
public:
	//
	// @brief 根据索引号，获取参数
	//
	static bool getParamByIndexW(const int index, glStringW & param);
	//
	// @brief 判断指定参数是否存在，并返回对应的索引号
	//
	static bool isParamExistW(const wchar_t * param, int * index);
	//
	// @brief 判断是否存在 switchName 参数，并返回下一个参数
	// @desc
	//
	// 假设命令行是下面这个样子的：
	//
	// C:\Windows\notepad.exe -mode text -power on
	//
	// 那么下面代码中，字符串变量 value 将保存 "text" 内容：
	//
	// glStringW value;
	// glCmdLine::getSwitchValueW(L"-mode", value);
	//
	static bool getSwitchValueW(const wchar_t * switchName, glStringW & value);
};

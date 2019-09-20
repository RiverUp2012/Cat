
#pragma once

#include "glString.h"

//
// @brief 网络助手类
//
class glNetHelper {
public:
	//
	// @brief 获取本地机器的 IPv4 地址
	//
	static bool getLocalMachineIPv4W(glStringW & ipV4);
	static bool getLocalMachineIPv4A(glStringA & ipV4);
};

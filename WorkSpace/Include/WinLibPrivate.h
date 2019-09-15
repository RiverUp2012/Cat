
#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <gdiplus.h>
#include <stdio.h>

//
// @brief GDI+ 启动类
// @desc 用于自动启动与关闭 GDI+ 库
//
class wlGDIPStartup {
public:
	static void startup(void);
	static void shutdown(void);
};

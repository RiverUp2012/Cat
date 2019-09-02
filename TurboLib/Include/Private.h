
#ifndef PRIVATE_H
#define PRIVATE_H

#include "../TurboLib.h"

//---------------------------------------------------------------
// 包含平台相关头文件
//---------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN
#define INITGUID
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <Windows.h>
#include <MMSystem.h>
#include <shellapi.h>
#include <WinSock2.h>
#include <TlHelp32.h>

//---------------------------------------------------------------
// window
// 窗口相关接口
//---------------------------------------------------------------

//
// 获取窗口句柄
//
extern HWND TWindowGetHandle(
	T_OBJECT window);

//---------------------------------------------------------------
// module
// 模块相关接口
//---------------------------------------------------------------

//
// 获取模块句柄
//
extern HMODULE TModuleGetHandle(
	T_OBJECT module);

#endif // PRIVATE_H


#ifndef PRIVATE_H
#define PRIVATE_H

#include "../TurboLib.h"

//---------------------------------------------------------------
// ����ƽ̨���ͷ�ļ�
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
// ������ؽӿ�
//---------------------------------------------------------------

//
// ��ȡ���ھ��
//
extern HWND TWindowGetHandle(
	T_OBJECT window);

//---------------------------------------------------------------
// module
// ģ����ؽӿ�
//---------------------------------------------------------------

//
// ��ȡģ����
//
extern HMODULE TModuleGetHandle(
	T_OBJECT module);

#endif // PRIVATE_H

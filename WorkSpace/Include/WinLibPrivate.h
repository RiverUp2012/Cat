
#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <gdiplus.h>
#include <stdio.h>

//
// @brief GDI+ ������
// @desc �����Զ�������ر� GDI+ ��
//
class wlGDIPStartup {
public:
	static void startup(void);
	static void shutdown(void);
};

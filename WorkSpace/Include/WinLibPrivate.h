
#pragma once

#include <Windows.h>
#include <gdiplus.h>

//
// @brief GDI+ ������
// @desc �����Զ�������ر� GDI+ ��
//
class wlGDIPStartup {
public:
	static void create(void);
	static void destroy(void);
};

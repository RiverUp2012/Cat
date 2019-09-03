
#include "stdafx.h"
#include "CGDIPStartup.h"

namespace
{
	// �Ƿ��Ѿ�������
	static bool gStartupFlag = false;
	static ULONG_PTR gToken = 0;
}

void CGDIPStartup::startup()
{
	Gdiplus::GdiplusStartupInput startupInput = { 0 };

	if (!gStartupFlag)
	{
		Gdiplus::GdiplusStartup(&gToken, &startupInput, 0);
		gStartupFlag = true;
	}
}

void CGDIPStartup::shutdown()
{
	if (gStartupFlag)
	{
		Gdiplus::GdiplusShutdown(gToken);
		gStartupFlag = false;
	}
}

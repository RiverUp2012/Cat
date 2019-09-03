
#include "stdafx.h"
#include "CCatApp.h"
#include "CMainDlg.h"
#include "GDIPlus/CGDIPStartup.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

// 应用程序实例名称
#define INSTANCE_EVENT_NAME (L"CatInstanceEvent")

static CCatApp gApp;
// 应用程序实例事件，用于防止多重实例启动
static T_OBJECT gInstanceEvent = 0;

BOOL CCatApp::InitInstance()
{
	// 防止多重实例启动

	bool requireQuit = false;

	gInstanceEvent = TEventOpenW(INSTANCE_EVENT_NAME);
	if (gInstanceEvent)
	{
		requireQuit = true;

		TEventDestroy(gInstanceEvent);
		gInstanceEvent = 0;
	}

	if (requireQuit)
	{
		return FALSE;
	}

	gInstanceEvent = TEventCreateW(T_FALSE, T_FALSE, INSTANCE_EVENT_NAME);
	if (!gInstanceEvent)
	{
		return FALSE;
	}

	// 启动日志

	wchar_t logFileName[520] = { 0 };
	TDirectoryGetAppW(logFileName, _countof(logFileName));
	wcscat_s(logFileName, L"Cat.log");
	TLogStartupW(logFileName, T_TRUE);

	// 启动 GDI+

	CGDIPStartup::startup();

	// 启动 App

	CWinApp::InitInstance();

	// 启动主对话框

	CMainDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// 关闭 GDI+

	CGDIPStartup::shutdown();

	// 关闭日志

	TLogShutdown();

	if (gInstanceEvent)
	{
		TEventDestroy(gInstanceEvent);
		gInstanceEvent = 0;
	}

	return FALSE;
}

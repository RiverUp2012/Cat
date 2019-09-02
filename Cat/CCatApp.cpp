
#include "stdafx.h"
#include "CCatApp.h"
#include "CMainDlg.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

CCatApp theApp;

BOOL CCatApp::InitInstance()
{
	// 启动日志

	wchar_t logFileName[520] = { 0 };
	TDirectoryGetAppW(logFileName, _countof(logFileName));
	wcscat_s(logFileName, L"Cat.Log.txt");
	TLogStartupW(logFileName, T_TRUE);

	CWinApp::InitInstance();

	CMainDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// 关闭日志

	TLogShutdown();

	return FALSE;
}

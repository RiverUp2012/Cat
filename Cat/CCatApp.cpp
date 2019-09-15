
#include "stdafx.h"
#include "CCatApp.h"
#include "CMainDlg.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

static CCatApp gApp;
static wlSingleAppInstance gSingleAppInstance;

BOOL CCatApp::InitInstance() {
	// 防止多重实例启动

	if (gSingleAppInstance.checkW(L"CatInstanceName")) {
		return TRUE;
	}

	// 启动日志

	// 启动 App

	CWinApp::InitInstance();

	// 启动主对话框

	CMainDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// 关闭日志

	return FALSE;
}

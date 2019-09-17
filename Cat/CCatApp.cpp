
#include "stdafx.h"
#include "CCatApp.h"
#include "CMainDlg.h"
#include "CBio4MemCheatDlg.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

static CCatApp gApp;
static glSingleAppInstance gSingleAppInstance;

BOOL CCatApp::InitInstance() {

	// 防止多重实例启动

	if (gSingleAppInstance.checkW(L"CatInstanceName")) {
		return TRUE;
	}

	// 启动日志

	glStringW logFileName;
	glPathHelper::getAppPathW(logFileName);
	glLog::createW(logFileName + L"Cat.log");
	glLog::setOutputDebugView(true);

	// 启动 App

	CWinApp::InitInstance();

	// 启动主对话框

	//CMainDlg dlg;
	CBio4MemCheatDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// 关闭日志

	glLog::destroy();

	// 关闭异步任务队列

	glAsyncTaskQueue::quit();

	// 关闭定时器系统

	glTimerSystem::quit();

	return FALSE;
}


#include "stdafx.h"
#include "CCatApp.h"
#include "CMainDlg.h"
#include "CBio4MemCheatDlg.h"
#include "CProcessCleanupSettingDlg.h"
#include "CRemoteControlServerDlg.h"
#include "CRemoteControlClientDlg.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

static CCatApp gApp;

BOOL CCatApp::InitInstance() {

	// 防止多重实例启动

	//if (checkSingleAppInstanceW(L"CatInstanceName")) {
	//return TRUE;
	//}

	// 启动日志

	glStringW appPath;
	glPathHelper::getAppPathW(appPath);
	glLog::createW(appPath + L"Cat.log");
	glLog::setOutputDebugView(true);
	glLog::setAutoAppendNewLine(true);

	// 启动 App

	CWinApp::InitInstance();

	// 启动主对话框

	CMainDlg mainDlg;
	CBio4MemCheatDlg bio4MemCheatDlg;
	CProcessCleanupSettingDlg processCleanupSettingDlg;	
	CRemoteControlClientDlg remoteControlClientDlg;
	CRemoteControlServerDlg remoteControlServerDlg;

	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
		m_pMainWnd = &bio4MemCheatDlg;
		bio4MemCheatDlg.DoModal();
	}
	else {
		m_pMainWnd = &bio4MemCheatDlg;
		bio4MemCheatDlg.DoModal();
	}

	// 关闭日志

	glLog::destroy();

	// 关闭异步任务队列

	glAsyncTaskQueue::quit();

	// 关闭定时器系统

	glTimerSystem::quit();

	return FALSE;
}

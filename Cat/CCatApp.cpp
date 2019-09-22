
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

	// ��ֹ����ʵ������

	//if (checkSingleAppInstanceW(L"CatInstanceName")) {
	//return TRUE;
	//}

	// ������־

	glStringW appPath;
	glPathHelper::getAppPathW(appPath);
	glLog::createW(appPath + L"Cat.log");
	glLog::setOutputDebugView(true);
	glLog::setAutoAppendNewLine(true);

	// ���� App

	CWinApp::InitInstance();

	// �������Ի���

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

	// �ر���־

	glLog::destroy();

	// �ر��첽�������

	glAsyncTaskQueue::quit();

	// �رն�ʱ��ϵͳ

	glTimerSystem::quit();

	return FALSE;
}

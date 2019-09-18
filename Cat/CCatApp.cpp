
#include "stdafx.h"
#include "CCatApp.h"
#include "CMainDlg.h"
#include "CBio4MemCheatDlg.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

static CCatApp gApp;

BOOL CCatApp::InitInstance() {

	// ��ֹ����ʵ������

	if (checkSingleAppInstanceW(L"CatInstanceName")) {
		return TRUE;
	}

	// ������־

	glStringW appPath;
	glPathHelper::getAppPathW(appPath);
	glLog::createW(appPath + L"Cat.log");
	glLog::setOutputDebugView(true);

	// ���� App

	CWinApp::InitInstance();

	// �������Ի���

	CMainDlg dlg;
	//CBio4MemCheatDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// �ر���־

	glLog::destroy();

	// �ر��첽�������

	glAsyncTaskQueue::quit();

	// �رն�ʱ��ϵͳ

	glTimerSystem::quit();

	return FALSE;
}

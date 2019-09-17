
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
	// ��ֹ����ʵ������

	if (gSingleAppInstance.checkW(L"CatInstanceName")) {
		return TRUE;
	}

	// ������־

	glStringW logFileName;
	glPathHelper::getAppPathW(logFileName);
	logFileName += L"Cat.log";
	glLog::createW(logFileName.getString());
	glLog::setOutputDebugView(true);

	// ���� App

	CWinApp::InitInstance();

	// �������Ի���

	//CMainDlg dlg;
	CBio4MemCheatDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// �ر���־

	glLog::destroy();

	return FALSE;
}

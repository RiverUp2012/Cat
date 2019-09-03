
#include "stdafx.h"
#include "CCatApp.h"
#include "CMainDlg.h"
#include "GDIPlus/CGDIPStartup.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

// Ӧ�ó���ʵ������
#define INSTANCE_EVENT_NAME (L"CatInstanceEvent")

static CCatApp gApp;
// Ӧ�ó���ʵ���¼������ڷ�ֹ����ʵ������
static T_OBJECT gInstanceEvent = 0;

BOOL CCatApp::InitInstance()
{
	// ��ֹ����ʵ������

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

	// ������־

	wchar_t logFileName[520] = { 0 };
	TDirectoryGetAppW(logFileName, _countof(logFileName));
	wcscat_s(logFileName, L"Cat.log");
	TLogStartupW(logFileName, T_TRUE);

	// ���� GDI+

	CGDIPStartup::startup();

	// ���� App

	CWinApp::InitInstance();

	// �������Ի���

	CMainDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// �ر� GDI+

	CGDIPStartup::shutdown();

	// �ر���־

	TLogShutdown();

	if (gInstanceEvent)
	{
		TEventDestroy(gInstanceEvent);
		gInstanceEvent = 0;
	}

	return FALSE;
}


#include "stdafx.h"
#include "CCatApp.h"
#include "CMainDlg.h"
#include "CBio4MemCheatDlg.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

static CCatApp gApp;
static glSingleAppInstance gSingleAppInstance;

class MyTask : public glAsyncTask {
public:
	MyTask(const int completeCallbackID) {
		mCompleteCallbackID = completeCallbackID;
	}
public:
	virtual void onAsyncTaskRun(void) override {
		Sleep(3000);
		glAsyncTaskCompleteCallback * completeCallback = 0;
		glAsyncTaskCompleteCallbackResourcePool::getResource(
			mCompleteCallbackID,
			completeCallback,
			true);
		if (completeCallback) {
			completeCallback->onAsyncTaskComplete();
		}
	}
private:
	int mCompleteCallbackID;
};

class MyCompleteCallback : public glAsyncTaskCompleteCallback {
public:
	MyCompleteCallback() {
	}
	virtual ~MyCompleteCallback() {
		glAsyncTaskCompleteCallbackResourcePool::markResourceUnuse(this);
	}
public:
	virtual void onAsyncTaskComplete(void) override {
		::MessageBoxW(::GetDesktopWindow(), L"DDD", L"AAA", 0);
	}
};

BOOL CCatApp::InitInstance() {

	//--------------------------------------------------------
	// ���Դ���
	//--------------------------------------------------------

	int callbackID = 0;

	MyCompleteCallback * callback = new MyCompleteCallback();
	glAsyncTaskCompleteCallbackResourcePool::insertResource(callback, callbackID);

	MyTask * task = new MyTask(callbackID);
	glAsyncTaskQueue::postTask(task);
	task->release();

	//delete callback;
	//callback = 0;

	//--------------------------------------------------------
	// ���Դ���
	//--------------------------------------------------------

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

	glAsyncTaskQueue::quit();

	return FALSE;
}

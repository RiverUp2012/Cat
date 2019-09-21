
#include "stdafx.h"
#include "resource.h"
#include "CMainDlg.h"
#include "RemoteControl/CRemoteControlServer.h"
#include "RemoteControl/CRemoteControlClient.h"
#include "ProcessCleanup/CProcessCleanup.h"
#include "ProcessCleanup/CProcessCleanupConfigFile.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_NCHITTEST()
	ON_WM_SYSCOMMAND()
	ON_WM_DEVICECHANGE()
END_MESSAGE_MAP()

CMainDlg::CMainDlg(CWnd* parent) :
	CDialogEx(IDD_DLG_MAIN, parent) {
	mIconHandle = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BOOL CMainDlg::OnInitDialog() {
	glStringW appPath;

	CDialogEx::OnInitDialog();
	SetIcon(mIconHandle, TRUE);
	SetIcon(mIconHandle, FALSE);

	// 绘制猫猫背景

	glPathHelper::getAppPathW(appPath);

	if (createFromHWND(GetSafeHwnd())) {
		if (mImgBK.createFromResourceW(IDB_PNG_CAT, L"PNG")) {
			drawImage(mImgBK, 0, 0, mImgBK.getWidth(), mImgBK.getHeight());
			present();
		}
	}

	return TRUE;
}

void CMainDlg::OnOK(void) {

}

void CMainDlg::OnCancel(void) {

}

LRESULT CMainDlg::OnNcHitTest(CPoint point) {
	return HTCAPTION;
}

void CMainDlg::adjustWindowPosToDesktopBottomRight(void) {

}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if (SC_CLOSE == nID) {
		EndDialog(0);
	}
	__super::OnSysCommand(nID, lParam);
}

BOOL CMainDlg::OnDeviceChange(UINT nEventType, DWORD_PTR dwData) {
	// 有硬件设备产生改变
	return __super::OnDeviceChange(nEventType, dwData);
}

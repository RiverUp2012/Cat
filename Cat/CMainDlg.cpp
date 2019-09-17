
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
END_MESSAGE_MAP()

CMainDlg::CMainDlg(CWnd* pParent) : CDialogEx(IDD_DLG_MAIN, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BOOL CMainDlg::OnInitDialog() {
	glStringW imageFileName;
	glStringW appPath;

	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// ªÊ÷∆√®√®±≥æ∞

	glPathHelper::getAppPathW(appPath);

	if (createFromHWND(GetSafeHwnd())) {
		imageFileName = appPath + L"Cat\\Image\\Cat.png";
		if (mImgBK.createFromFileW(imageFileName)) {
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

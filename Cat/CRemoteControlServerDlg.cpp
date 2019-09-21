
#include "stdafx.h"
#include "CRemoteControlServerDlg.h"
#include "resource.h"
#include "RemoteControl/CRemoteControlServer.h"
#include "Common/CMFCHelper.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CRemoteControlServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BTN_SERVER_STARTUP, &CRemoteControlServerDlg::OnBnClickedBtnServerStartup)
	ON_BN_CLICKED(IDC_BTN_SERVER_SHUTDOWN, &CRemoteControlServerDlg::OnBnClickedBtnServerShutdown)
END_MESSAGE_MAP()

CRemoteControlServerDlg::CRemoteControlServerDlg(CWnd * parent) :
	CDialogEx(IDD_DLG_REMOTE_CONTROL_SERVER, parent) {
	mIconHandle = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CRemoteControlServerDlg::~CRemoteControlServerDlg() {
	mEditOutput.Detach();
}

BOOL CRemoteControlServerDlg::OnInitDialog() {
	glStringW localMachineIPv4;
	CDialogEx::OnInitDialog();
	SetIcon(mIconHandle, TRUE);
	SetIcon(mIconHandle, FALSE);
	if (CMFCHelper::attachDialogControl(this, &mEditOutput, IDC_EDIT_OUTPUT)) {
		if (glNetHelper::getLocalMachineIPv4W(localMachineIPv4)) {
			mEditOutput.SetSel(-1);
			mEditOutput.ReplaceSel(localMachineIPv4);
		}
	}
	return TRUE;
}

void CRemoteControlServerDlg::OnOK(void) {

}

void CRemoteControlServerDlg::OnCancel(void) {

}

void CRemoteControlServerDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if (SC_CLOSE == nID) {
		EndDialog(0);
	}
	__super::OnSysCommand(nID, lParam);
}

void CRemoteControlServerDlg::OnBnClickedBtnServerStartup() {
	CRemoteControlServer::startup();
}

void CRemoteControlServerDlg::OnBnClickedBtnServerShutdown() {
	CRemoteControlServer::shutdown();
}

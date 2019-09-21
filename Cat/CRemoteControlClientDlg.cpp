
#include "stdafx.h"
#include "CRemoteControlClientDlg.h"
#include "resource.h"
#include "RemoteControl/CRemoteControlClient.h"
#include "Common/CMFCHelper.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CRemoteControlClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BTN_REQUEST_USER_NAME, &CRemoteControlClientDlg::OnBnClickedBtnRequestUserName)
END_MESSAGE_MAP()

CRemoteControlClientDlg::CRemoteControlClientDlg(CWnd * parent) :
	CDialogEx(IDD_DLG_REMOTE_CONTROL_CLIENT, parent) {
	mIconHandle = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CRemoteControlClientDlg::~CRemoteControlClientDlg() {
	mEditOutput.Detach();
}

BOOL CRemoteControlClientDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	SetIcon(mIconHandle, TRUE);
	SetIcon(mIconHandle, FALSE);
	if (CMFCHelper::attachDialogControl(this, &mEditOutput, IDC_EDIT_OUTPUT)) {

	}
	return TRUE;
}

void CRemoteControlClientDlg::OnOK(void) {

}

void CRemoteControlClientDlg::OnCancel(void) {

}

void CRemoteControlClientDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if (SC_CLOSE == nID) {
		EndDialog(0);
	}
	__super::OnSysCommand(nID, lParam);
}

void CRemoteControlClientDlg::OnBnClickedBtnRequestUserName() {
	glStringW userName;
	if (CRemoteControlClient::requestUserNameW(userName, L"192.168.1.100")) {

	}
}

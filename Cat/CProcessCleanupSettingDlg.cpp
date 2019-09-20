
#include "stdafx.h"
#include "CProcessCleanupSettingDlg.h"
#include "ProcessCleanup/CProcessCleanup.h"
#include "ProcessCleanup/CProcessCleanupConfigFile.h"
#include "resource.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CProcessCleanupSettingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BTN_REMOVE_SELECTED_PROCESS, &CProcessCleanupSettingDlg::OnBnClickedBtnRemoveSelectedProcess)
	ON_BN_CLICKED(IDC_BTN_ADD_PROCESS, &CProcessCleanupSettingDlg::OnBnClickedBtnAddProcess)
	ON_BN_CLICKED(IDC_BTN_OK, &CProcessCleanupSettingDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_PROCESS_CLEANUP_STOP, &CProcessCleanupSettingDlg::OnBnClickedBtnProcessCleanupStop)
	ON_BN_CLICKED(IDC_BTN_PROCESS_CLEANUP_START, &CProcessCleanupSettingDlg::OnBnClickedBtnProcessCleanupStart)
END_MESSAGE_MAP()

CProcessCleanupSettingDlg::CProcessCleanupSettingDlg(CWnd * parent) :
	CDialogEx(IDD_DLG_PROCESS_CLEANUP_CONFIG, parent) {
	mIconHandle = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CProcessCleanupSettingDlg::~CProcessCleanupSettingDlg() {

}

BOOL CProcessCleanupSettingDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	SetIcon(mIconHandle, TRUE);
	SetIcon(mIconHandle, FALSE);
	return TRUE;
}

void CProcessCleanupSettingDlg::OnOK(void) {

}

void CProcessCleanupSettingDlg::OnCancel(void) {

}

void CProcessCleanupSettingDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if (SC_CLOSE == nID) {
		EndDialog(0);
	}
	__super::OnSysCommand(nID, lParam);
}

void CProcessCleanupSettingDlg::OnBnClickedBtnRemoveSelectedProcess() {

}

void CProcessCleanupSettingDlg::OnBnClickedBtnAddProcess() {

}

void CProcessCleanupSettingDlg::OnBnClickedBtnOk() {
	EndDialog(0);
}

void CProcessCleanupSettingDlg::OnBnClickedBtnProcessCleanupStop() {
	CProcessCleanup::shutdown();
}

void CProcessCleanupSettingDlg::OnBnClickedBtnProcessCleanupStart() {
	CProcessCleanup::startup(0);
}

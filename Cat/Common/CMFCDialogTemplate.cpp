
#include "stdafx.h"
#include "CMFCDialogTemplate.h"
#include "resource.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMFCDialogTemplate, CDialogEx)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

CMFCDialogTemplate::CMFCDialogTemplate(CWnd * parent) : CDialogEx(1, parent) {
	mIconHandle = 0;
}

CMFCDialogTemplate::~CMFCDialogTemplate() {

}

BOOL CMFCDialogTemplate::OnInitDialog() {
	CDialogEx::OnInitDialog();
	SetIcon(mIconHandle, TRUE);
	SetIcon(mIconHandle, FALSE);
	return TRUE;
}

void CMFCDialogTemplate::OnOK(void) {

}

void CMFCDialogTemplate::OnCancel(void) {

}

void CMFCDialogTemplate::OnSysCommand(UINT nID, LPARAM lParam) {
	if (SC_CLOSE == nID) {
		EndDialog(0);
	}
	__super::OnSysCommand(nID, lParam);
}

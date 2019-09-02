
#include "stdafx.h"
#include "CCatApp.h"
#include "CMainDlg.h"
#include "afxdialogex.h"
#include "RemoteControl/CRemoteControlServer.h"
#include "RemoteControl/CRemoteControlClient.h"

#ifdef _DEBUG
#	define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

CMainDlg::CMainDlg(CWnd* pParent)
	: CDialogEx(CMainDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return TRUE;
}

LRESULT CMainDlg::OnNcHitTest(CPoint point)
{
	return HTCAPTION;
}


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
END_MESSAGE_MAP()

CMainDlg::CMainDlg(CWnd* pParent) : CDialogEx(IDD_DLG_MAIN, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BOOL CMainDlg::OnInitDialog() {
	glStringW imageFileName;
	glStringW configFileName;
	glStringW appPath;

	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	wlPathHelper::getAppPathW(appPath);

	// 绘制猫猫背景

	if (createFromHWND(GetSafeHwnd())) {
		imageFileName = appPath + L"Cat\\Image\\Cat.png";
		if (mImgBK.createFromFileW(imageFileName.getString())) {
			drawImage(mImgBK, 0, 0, mImgBK.getWidth(), mImgBK.getHeight());
			present();
		}
	}

	// 从配置文件加载要清理的进程列表

	configFileName = appPath +  L"Cat\\Config\\ProcessCleanup.ini";
	CProcessCleanupConfigFile::loadW(configFileName.getString());

	// 将要清理的进程告诉进程清理模块

	for (const auto & processExeFileName : CProcessCleanupConfigFile::getProcessExeFileNameList()) {
		CProcessCleanup::addProcessExeFileNameW(processExeFileName.c_str());
	}

	// 启动进程清理模块

	CProcessCleanup::startup(0);

	return TRUE;
}

LRESULT CMainDlg::OnNcHitTest(CPoint point) {
	return HTCAPTION;
}

void CMainDlg::adjustWindowPosToDesktopBottomRight(void) {

}


#pragma once

//
// 主对话框类
//
class CMainDlg : public CDialogEx, public wlGDIPWindow {
public:
	CMainDlg(CWnd * pParent = 0);
private:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual void OnOK(void);
	virtual void OnCancel(void);
	afx_msg LRESULT OnNcHitTest(CPoint point);
private:
	//
	// 令窗口向桌面右下角靠拢
	//
	void adjustWindowPosToDesktopBottomRight(void);
private:
	HICON m_hIcon;
	wlGDIPImage mImgBK;
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};

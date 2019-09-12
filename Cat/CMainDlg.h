
#pragma once

//
// 主对话框类
//
class CMainDlg : public CDialogEx, public wl::GDIPWindow
{
public:

	CMainDlg(CWnd * pParent = 0);

protected:

	HICON m_hIcon = 0;
	wl::GDIPImage mImgBK;

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:

	afx_msg LRESULT OnNcHitTest(CPoint point);

private:

	//
	// 令窗口向桌面右下角靠拢
	//
	void adjustWindowPosToDesktopBottomRight(void);
};

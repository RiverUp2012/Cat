
#pragma once

//
// 主对话框类
//
class CMainDlg : public CDialogEx
{
public:

	CMainDlg(CWnd * pParent = 0);

protected:

	HICON m_hIcon = 0;
	CDC * mDC = 0;
	CDC mMemDC;
	CBitmap mMemBmp;
	Gdiplus::Graphics * mGraphics = 0;
	Gdiplus::Image * mImgBk = 0;
	CRect mClientRect;

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:

	afx_msg LRESULT OnNcHitTest(CPoint point);

private:

	void onDraw(void);

	//
	// 令窗口向桌面右下角靠拢
	//
	void adjustWindowPosToDesktopBottomRight(void);
};

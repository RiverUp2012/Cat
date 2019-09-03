
#pragma once

//
// ���Ի�����
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
	// ������������½ǿ�£
	//
	void adjustWindowPosToDesktopBottomRight(void);
};

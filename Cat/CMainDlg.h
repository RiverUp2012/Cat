
#pragma once

//
// ���Ի�����
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
	// ������������½ǿ�£
	//
	void adjustWindowPosToDesktopBottomRight(void);
};

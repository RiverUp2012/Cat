
#pragma once

//
// ���Ի�����
//
class CMainDlg : public CDialogEx, public wlGDIPWindow
{
public:

	CMainDlg(CWnd * pParent = 0);

protected:

	HICON m_hIcon = 0;
	wlGDIPImage mImgBK;

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

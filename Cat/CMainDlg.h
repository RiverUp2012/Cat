
#pragma once

//
// 主对话框类
//
class CMainDlg : public CDialogEx
{
public:

	CMainDlg(CWnd * pParent = 0);

	enum { IDD = IDD_DLG_MAIN };

protected:

	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
};

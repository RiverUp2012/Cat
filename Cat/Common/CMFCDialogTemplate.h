
#pragma once

class CMFCDialogTemplate : public CDialogEx {
public:
	CMFCDialogTemplate(CWnd * parent = 0);
	virtual ~CMFCDialogTemplate();
public:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual void OnOK(void);
	virtual void OnCancel(void);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
private:
	HICON mIconHandle;
};

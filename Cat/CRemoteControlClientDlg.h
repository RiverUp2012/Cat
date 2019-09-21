
#pragma once

class CRemoteControlClientDlg : public CDialogEx {
public:
	CRemoteControlClientDlg(CWnd * parent = 0);
	virtual ~CRemoteControlClientDlg();
public:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual void OnOK(void);
	virtual void OnCancel(void);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedBtnRequestUserName();
private:
	HICON mIconHandle;
	CEdit mEditOutput;
};

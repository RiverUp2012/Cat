
#pragma once

class CRemoteControlServerDlg : public CDialogEx {
public:
	CRemoteControlServerDlg(CWnd * parent = 0);
	virtual ~CRemoteControlServerDlg();
public:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual void OnOK(void);
	virtual void OnCancel(void);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedBtnServerStartup();
	afx_msg void OnBnClickedBtnServerShutdown();
private:
	HICON mIconHandle;
	CEdit mEditOutput;
};

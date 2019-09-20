
#pragma once

class CProcessCleanupSettingDlg : public CDialogEx {
public:
	CProcessCleanupSettingDlg(CWnd * parent = 0);
	virtual ~CProcessCleanupSettingDlg();
public:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual void OnOK(void);
	virtual void OnCancel(void);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
private:
	HICON mIconHandle;
public:
	afx_msg void OnBnClickedBtnRemoveSelectedProcess();
	afx_msg void OnBnClickedBtnAddProcess();
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnProcessCleanupStop();
	afx_msg void OnBnClickedBtnProcessCleanupStart();
};

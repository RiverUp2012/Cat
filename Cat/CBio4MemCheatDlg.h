
#pragma once

//
// @brief ����Σ�� 4 �ڴ��޸ĶԻ�����
//
class CBio4MemCheatDlg : public CDialogEx {
public:
	CBio4MemCheatDlg(CWnd* pParent = 0);
	~CBio4MemCheatDlg();
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog(void);
	virtual void OnOK(void);
	virtual void OnCancel(void);
	afx_msg void OnBnClickedBtnHowTo();
	afx_msg void OnBnClickedBtnSetup();
	afx_msg void OnBnClickedBtnShutdown();
	afx_msg void OnCbnSelchangeCbBio4Version();
	afx_msg void OnBnClickedBtnAddCurrentItemCount();
	afx_msg void OnBnClickedBtnAddHp();
	afx_msg void OnBnClickedBtnAddCurrentGunBullet();
	afx_msg void OnBnClickedBtnAddPtas();
private:
	HICON m_hIcon;
	CComboBox mCBBio4Ver; // ��Ϸ�汾�����б�
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};

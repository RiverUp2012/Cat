
#pragma once

class CBio4MemCheatDlg : public CDialogEx
{
public:
	CBio4MemCheatDlg(CWnd* pParent = 0);
	virtual ~CBio4MemCheatDlg();
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog(void);
private:
	CComboBox mCBBio4Ver; // 游戏版本下拉列表
public:
	afx_msg void OnBnClickedBtnHowTo();
	afx_msg void OnBnClickedBtnSetup();
	afx_msg void OnBnClickedBtnShutdown();
	afx_msg void OnCbnSelchangeCbBio4Version();
	afx_msg void OnBnClickedBtnAddCurrentItemCount();
	afx_msg void OnBnClickedBtnAddHp();
	afx_msg void OnBnClickedBtnAddCurrentGunBullet();
	afx_msg void OnBnClickedBtnAddPtas();
};


#pragma once

//
// @brief ���Ի�����
//
class CMainDlg : public CDialogEx, public wlGDIPWindow {
public:
	CMainDlg(CWnd * pParent = 0);
private:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual void OnOK(void);
	virtual void OnCancel(void);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD_PTR dwData);
private:
	//
	// @brief ������������½ǿ�£
	//
	void adjustWindowPosToDesktopBottomRight(void);
private:
	HICON m_hIcon;
	wlGDIPImage mImgBK; // ����ͼ��
};

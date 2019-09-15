
#pragma once

//
// @brief MFC 助手类
//
class CMFCHelper {
public:
	//
	// @brief 绑定对话框控件
	//
	static bool attachDialogControl(CDialog * dlg, CWnd * control, const int controlID);
};

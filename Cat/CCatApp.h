
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

//
// @brief Ӧ�ó�����
//
class CCatApp : public CWinApp, public glSingleAppInstanceChecker {
public:

	virtual BOOL InitInstance();
};

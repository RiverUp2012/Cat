
#pragma once

#include "glString.h"

//
// @brief ��������
//
class glCmdLine {
public:
	//
	// @brief ���������ţ���ȡ����
	//
	static bool getParamByIndexW(const int index, glStringW & param);
	//
	// @brief �ж�ָ�������Ƿ���ڣ������ض�Ӧ��������
	//
	static bool isParamExistW(const wchar_t * param, int * index);
	//
	// @brief �ж��Ƿ���� switchName ��������������һ������
	// @desc
	//
	// ����������������������ӵģ�
	//
	// C:\Windows\notepad.exe -mode text -power on
	//
	// ��ô��������У��ַ������� value ������ "text" ���ݣ�
	//
	// glStringW value;
	// glCmdLine::getSwitchValueW(L"-mode", value);
	//
	static bool getSwitchValueW(const wchar_t * switchName, glStringW & value);
};

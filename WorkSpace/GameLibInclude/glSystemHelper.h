
#pragma once

#include "glString.h"

struct glMemoryInfo;

//
// @brief ϵͳ������
//
class glSystemHelper {
public:
	//
	// @brief ��ȡ��ǰ��¼�û���
	//
	static bool getCurrentUserNameW(glStringW & userName);
	//
	// @brief ��ȡϵͳĿ¼·��
	//
	static bool getSystemDirectoryW(glStringW & systemDir);
	//
	// @brief ��ȡ Windows Ŀ¼·��
	//
	static bool getWindowDirectoryW(glStringW & windowDir);
	//
	// @brief ��ȡ���������
	//
	static bool getComputerNameW(glStringW & computerName);
	//
	// @brief ��ȡ�ڴ���Ϣ
	//
	static bool getMemoryInfo(glMemoryInfo & memoryInfo);
};

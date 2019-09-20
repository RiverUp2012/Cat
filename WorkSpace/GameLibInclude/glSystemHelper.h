
#pragma once

#include "glString.h"

struct glMemoryInfo;

//
// @brief ����ϵͳ�汾ö����
//
enum
{
	GL_OSVER_FIRST,
	GL_OSVER_WIN2K,
	GL_OSVER_WINXP,
	GL_OSVER_WINXP_SP1,
	GL_OSVER_WINXP_SP2,
	GL_OSVER_WINXP_SP3,
	GL_OSVER_WINVISTA,
	GL_OSVER_WINVISTA_SP1,
	GL_OSVER_WINVISTA_SP2,
	GL_OSVER_WIN7,
	GL_OSVER_WIN7_SP1,
	GL_OSVER_WIN8,
	GL_OSVER_WIN81,
	GL_OSVER_WIN10,
};

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
	//
	// @brief ��ȡ����ϵͳ�汾
	//
	static bool getOSVersion(int & osVer);
};

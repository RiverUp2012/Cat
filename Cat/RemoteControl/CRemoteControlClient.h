
#pragma once

//
// @brief Զ�̿���ϵͳ���ͻ���
//
class CRemoteControlClient {
public:
	//
	// @brief ����
	//
	static bool startupW(const wchar_t * serverIPv4, const short int serverPort);
	//
	// @brief �ر�
	//
	static void shutdown(void);
	//
	// @brief �����û���
	//
	static bool requestUserNameW(glStringW & userName);
};

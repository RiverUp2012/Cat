
#pragma once

//
// Զ�̿���ϵͳ���ͻ���
//
class CRemoteControlClient
{
public:

	//
	// ����
	//
	static void startup(void);

	//
	// �ر�
	//
	static void shutdown(void);

	//
	// �����û���
	//
	static bool requestUserNameW(
		wchar_t * userName,
		const int userNameSize);
};


#pragma once

//
// ����������
//
// �û����ȸ��߽���������Ҫ������Щ���̣�������������ں�̨����
// һ����ʱ���̣߳���ʱ��ѯϵͳ���Ƿ������Щ��Ҫ����Ľ���
// ����У����������
//
class CProcessCleanup {
public:

	//
	// ����
	//
	// cleanupTimeInterval ÿ�����ٺ�������һ�ν���
	//
	static void startup(
		const int cleanupTimeInterval);

	//
	// �ر�
	//
	static void shutdown(void);

	//
	// ���Ҫ����Ľ��� exe �ļ���
	//
	// processExeFileName Ҫ����Ľ��� exe �ļ���
	//
	static bool addProcessExeFileNameW(
		const wchar_t * processExeFileName);

	//
	// �Ƴ�����Ҫ����Ľ��� exe �ļ���
	//
	static void removeAllProcessExeFileName(void);
};

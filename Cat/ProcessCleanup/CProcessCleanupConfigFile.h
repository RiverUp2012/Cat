
#pragma once

//
// �������������ļ���
//
// ��������ģ��ͨ����������ļ�һ�������û�ͨ�� GUI ��������Ҫ������Щ
// ���̣����������������ļ��ཫ��Щ���̱��浽�����ϵ������ļ����´�����
// ����󣬳�����ȡ�����ļ����������һ�ε����ý�������
//
class CProcessCleanupConfigFile
{
public:

	//
	// �������ļ����ؽ����б�
	//
	static void loadW(
		const wchar_t * configFileName);

	//
	// �������õ������ļ�
	//
	static void saveW(
		const wchar_t * configFileName);

	//
	// ��ȡ�����б��е�һ������ exe �ļ���
	//
	static bool firstProcessExeFileNameW(
		wchar_t * processExeFileName,
		const int processExeFileNameSize);

	//
	// ��ȡ�����б�����һ������ exe �ļ���
	//
	static bool nextProcessExeFileNameW(
		wchar_t * processExeFileName,
		const int processExeFileNameSize);

	//
	// ���Ҫ����Ľ��� exe �ļ���
	//
	// processExeFileName Ҫ����Ľ��� exe �ļ���
	//
	static bool addProcessExeFileNameW(
		const wchar_t * processExeFileName);

	//
	// �Ƴ����� exe �ļ���
	//
	// processExeFileName Ҫ�Ƴ��Ľ��� exe �ļ���
	//
	static bool removeProcessExeFileNameW(
		const wchar_t * processExeFileName);

	//
	// �Ƴ�����Ҫ����Ľ��� exe �ļ���
	//
	static void removeAllProcessExeFileName(void);
};


#pragma once

//
// @brief �������������ļ���
//
// ��������ģ��ͨ����������ļ�һ�������û�ͨ�� GUI ��������Ҫ������Щ
// ���̣����������������ļ��ཫ��Щ���̱��浽�����ϵ������ļ����´�����
// ����󣬳�����ȡ�����ļ����������һ�ε����ý�������
//
class CProcessCleanupConfigFile {
public:

	//
	// @brief �������ļ����ؽ����б�
	// @param configFileName �����ļ��ļ���
	//
	static void loadW(
		const wchar_t * configFileName);

	//
	// @brief �������õ������ļ�
	//
	static void saveW(
		const wchar_t * configFileName);

	//
	// @brief ��ȡҪ����Ľ��� exe �ļ���
	//
	static const std::vector<std::wstring> & getProcessExeFileNameList(void);

	//
	// @brief ���Ҫ����Ľ��� exe �ļ���
	// @param processExeFileName Ҫ����Ľ��� exe �ļ���
	//
	static bool addProcessExeFileNameW(
		const wchar_t * processExeFileName);

	//
	// @brief �Ƴ����� exe �ļ���
	// @param processExeFileName Ҫ�Ƴ��Ľ��� exe �ļ���
	//
	static bool removeProcessExeFileNameW(
		const wchar_t * processExeFileName);

	//
	// @brief �Ƴ�����Ҫ����Ľ��� exe �ļ���
	//
	static void removeAllProcessExeFileName(void);
};

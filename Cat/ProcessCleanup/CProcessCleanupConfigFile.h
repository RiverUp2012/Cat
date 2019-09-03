
#pragma once

//
// 进程清理配置文件类
//
// 进程清理模块通常配合配置文件一起工作，用户通过 GUI 界面设置要清理哪些
// 进程，随后进程清理配置文件类将这些进程保存到磁盘上的配置文件，下次启动
// 程序后，程序会读取配置文件，按照最近一次的配置进行运作
//
class CProcessCleanupConfigFile
{
public:

	//
	// 从配置文件加载进程列表
	//
	static void loadW(
		const wchar_t * configFileName);

	//
	// 保存配置到配置文件
	//
	static void saveW(
		const wchar_t * configFileName);

	//
	// 获取进程列表中第一个进程 exe 文件名
	//
	static bool firstProcessExeFileNameW(
		wchar_t * processExeFileName,
		const int processExeFileNameSize);

	//
	// 获取进程列表中下一个进程 exe 文件名
	//
	static bool nextProcessExeFileNameW(
		wchar_t * processExeFileName,
		const int processExeFileNameSize);

	//
	// 添加要清理的进程 exe 文件名
	//
	// processExeFileName 要清理的进程 exe 文件名
	//
	static bool addProcessExeFileNameW(
		const wchar_t * processExeFileName);

	//
	// 移除进程 exe 文件名
	//
	// processExeFileName 要移除的进程 exe 文件名
	//
	static bool removeProcessExeFileNameW(
		const wchar_t * processExeFileName);

	//
	// 移除所有要清理的进程 exe 文件名
	//
	static void removeAllProcessExeFileName(void);
};

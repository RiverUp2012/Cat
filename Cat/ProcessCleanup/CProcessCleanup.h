
#pragma once

//
// 进程清理类
//
// 用户事先告诉进程清理类要清理哪些进程，进程清理类会在后台开启
// 一个定时器线程，定时查询系统中是否存在这些需要清理的进程
// 如果有，将其清理掉
//
class CProcessCleanup {
public:

	//
	// 启动
	//
	// cleanupTimeInterval 每隔多少毫秒清理一次进程
	//
	static void startup(
		const int cleanupTimeInterval);

	//
	// 关闭
	//
	static void shutdown(void);

	//
	// 添加要清理的进程 exe 文件名
	//
	// processExeFileName 要清理的进程 exe 文件名
	//
	static bool addProcessExeFileNameW(
		const wchar_t * processExeFileName);

	//
	// 移除所有要清理的进程 exe 文件名
	//
	static void removeAllProcessExeFileName(void);
};


#pragma once

class glAsyncTask;

//
// @brief 异步任务队列类
//
class glAsyncTaskQueue {
public:
	//
	// @brief 投递异步任务到队列中，并等待被调度
	//
	static void postTask(glAsyncTask * task);
	//
	// @brief 退出异步任务队列，将会关闭后台线程，并释放队列中的所有异步任务
	//
	static void quit(void);
};

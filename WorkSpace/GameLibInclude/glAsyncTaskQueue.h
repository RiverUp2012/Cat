
#pragma once

class glAsyncTask;

//
// @brief 异步任务队列类
//
class glAsyncTaskQueue {
public:
	static void postTask(glAsyncTask * task);
	static void quit(void);
};

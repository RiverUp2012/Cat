
#pragma once

class glAsyncTask;

//
// @brief �첽���������
//
class glAsyncTaskQueue {
public:
	static void postTask(glAsyncTask * task);
	static void quit(void);
};

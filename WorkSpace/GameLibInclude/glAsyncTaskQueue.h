
#pragma once

class glAsyncTask;

//
// @brief �첽���������
//
class glAsyncTaskQueue {
public:
	//
	// @brief Ͷ���첽���񵽶����У����ȴ�������
	//
	static void postTask(glAsyncTask * task);
	//
	// @brief �˳��첽������У�����رպ�̨�̣߳����ͷŶ����е������첽����
	//
	static void quit(void);
};

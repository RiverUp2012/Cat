
#pragma once

//
// @brief 异步任务完成回调接口类
//
class glAsyncTaskCompleteCallback {
public:
	//
	// @brief 处理异步任务完成逻辑
	//
	virtual void onAsyncTaskComplete(void) = 0;
};


#pragma once

//
// @brief 异步任务完成回调接口类
//
class glAsyncTaskCompleteCallback {
public:
	virtual void onAsyncTaskComplete(void) = 0;
};

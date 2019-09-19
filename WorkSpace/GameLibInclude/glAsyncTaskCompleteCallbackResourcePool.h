
#pragma once

class glAsyncTaskCompleteCallback;

//
// @brief 异步任务完成回调接口资源池
//
class glAsyncTaskCompleteCallbackResourcePool {
public:
	static bool insertResource(
		glAsyncTaskCompleteCallback * const & resource,
		int & id);
	static bool getResource(
		const int id,
		glAsyncTaskCompleteCallback * & resource,
		const bool markResourceUnuse = true);
	static bool markResourceUnuse(
		glAsyncTaskCompleteCallback * const & resource);
};

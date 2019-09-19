
#pragma once

class glAsyncTaskCompleteCallback;

//
// @brief 异步任务完成回调资源池
//
class glAsyncTaskCompleteCallbackResourcePool {
public:
	//
	// @brief 插入异步任务完成回调，并返回对应的 id
	//
	static bool insertResource(
		glAsyncTaskCompleteCallback * const & resource,
		int & id);
	//
	// @brief 通过 id 获取异步任务完成回调
	//
	static bool getResource(
		const int id,
		glAsyncTaskCompleteCallback * & resource,
		const bool markResourceUnuse = true);
	//
	// @brief 将指定的异步任务完成回调从资源池中移除
	//
	static bool markResourceUnuse(
		glAsyncTaskCompleteCallback * const & resource);
};

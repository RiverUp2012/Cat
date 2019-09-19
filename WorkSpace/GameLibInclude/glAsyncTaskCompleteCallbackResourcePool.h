
#pragma once

class glAsyncTaskCompleteCallback;

//
// @brief �첽������ɻص��ӿ���Դ��
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

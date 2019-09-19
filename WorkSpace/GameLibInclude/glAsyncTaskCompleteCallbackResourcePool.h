
#pragma once

class glAsyncTaskCompleteCallback;

//
// @brief �첽������ɻص���Դ��
//
class glAsyncTaskCompleteCallbackResourcePool {
public:
	//
	// @brief �����첽������ɻص��������ض�Ӧ�� id
	//
	static bool insertResource(
		glAsyncTaskCompleteCallback * const & resource,
		int & id);
	//
	// @brief ͨ�� id ��ȡ�첽������ɻص�
	//
	static bool getResource(
		const int id,
		glAsyncTaskCompleteCallback * & resource,
		const bool markResourceUnuse = true);
	//
	// @brief ��ָ�����첽������ɻص�����Դ�����Ƴ�
	//
	static bool markResourceUnuse(
		glAsyncTaskCompleteCallback * const & resource);
};

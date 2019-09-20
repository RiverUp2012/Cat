
#pragma once

//
// @brief 远程控制系统，客户端
//
class CRemoteControlClient {
public:
	//
	// @brief 启动
	//
	static bool startupW(const wchar_t * serverIPv4, const short int serverPort);
	//
	// @brief 关闭
	//
	static void shutdown(void);
	//
	// @brief 请求用户名
	//
	static bool requestUserNameW(glStringW & userName);
};


#pragma once

//
// @brief 远程控制系统，客户端
//
class CRemoteControlClient {
public:
	//
	// @brief 请求用户名
	//
	static bool requestUserNameW(
		glStringW & userName,
		const wchar_t * serverIPv4);
};

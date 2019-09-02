
#pragma once

//
// 远程控制系统，客户端
//
class CRemoteControlClient
{
public:

	//
	// 启动
	//
	static void startup(void);

	//
	// 关闭
	//
	static void shutdown(void);

	//
	// 请求用户名
	//
	static bool requestUserNameW(
		wchar_t * userName,
		const int userNameSize);
};

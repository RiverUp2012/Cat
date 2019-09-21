
#pragma once

//
// @brief 远程控制系统，服务端
//
class CRemoteControlServer {
public:
	//
	// @brief 启动
	//
	static bool startup(void);
	//
	// @brief 关闭
	//
	static void shutdown(void);
};

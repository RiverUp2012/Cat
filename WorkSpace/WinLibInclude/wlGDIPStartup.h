
#pragma once

//
// @brief GDI+ 启动类
// @desc 用于自动启动与关闭 GDI+ 库
//
class wlGDIPStartup {
public:
	static void create(void);
	static void destroy(void);
};

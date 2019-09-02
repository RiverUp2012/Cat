
#pragma once

//
// 远程控制系统公用头文件
//

// 服务端监听 ip 地址
#define REMOTE_CONTROL_IP ("127.0.0.1")
// 服务端监听端口
#define REMOTE_CONTROL_PORT (10086)
// 包签名
#define PACK_SIG ("PACK")
// 包版本号
#define PACK_VER_MAJOR (0)
// 包版本号
#define PACK_VER_MINOR (1)

//
// 协议枚举体
//
// 一种协议，相当于一种类型的网络请求
//
enum
{
	// 哨兵
	PROTOCOL_FIRST,
	// 客户端向服务端请求用户名称
	PROTOCOL_REQUEST_USER_NAME,
	// 服务端向客户端响应用户名称
	PROTOCOL_RESPONSE_USER_NAME,
	// 哨兵
	PROTOCOL_LAST,
};

//
// 网络数据包头
//
struct SPackHeader
{
	// 包签名
	unsigned char mSig[4];
	// 包版本号
	unsigned short int mVerMajor = 0;
	// 包版本号
	unsigned short int mVerMinor = 0;
	// 包体数据大小
	unsigned short int mPackSize = 0;
	// 协议类型
	unsigned short int mProtocol = PROTOCOL_FIRST;
};

//
// 网络数据包
//
struct SPack : public SPackHeader
{
	// 包体数据
	// 根据不同的协议类型，包体数据所包含的内容各异
	void * mData;
};

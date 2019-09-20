
#pragma once

//
// 远程控制系统公用头文件
//

//
// @brief 协议枚举体
// @desc
//
// 一种协议，等价于一种类型的网络数据包，对于不同协议类型的网络数据包
// 其网络数据的处理方式不尽相同
//
enum {
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
// @brief 网络数据包头
// @desc
//
// 通常，一个完整的网络数据包的内存模型如下：
//
// |------------------------|
// | 包头（必须）             |
// |------------------------|
// | 包体（可选）             |
// |------------------------|
//
// 包头用 SPackHeader 结构体描述，包体大小由包头结构体的 mPackSize 字段描述
// 根据不同的协议，包体的内容不尽相同，比如：对于客户端向服务端请求用户名时，不需要
// 附带包体，而服务端向客户端响应用户名请求时，包体包含用户名字符串，以此类推。
//
struct SPackHeader {
	// 包签名
	unsigned char mSig[4];
	// 包版本号
	unsigned short int mVerMajor = 0;
	// 包版本号
	unsigned short int mVerMinor = 0;
	// 包体数据大小，不包含包头
	unsigned short int mPackSize = 0;
	// 协议类型
	unsigned short int mProtocol = PROTOCOL_FIRST;
};

//
// @brief 网络数据包
//
struct SPack : public SPackHeader {
	// 包体数据
	// 根据不同的协议类型，包体数据所包含的内容各异
	void * mData;
};

//
// @brief 验证数据包是否有效
//
extern bool isPackValid(const SPackHeader & packHeader);

//
// @brief 填充数据包包头
//
extern void makePackHeader(SPackHeader & packHeader, const int protocol);

//
// @brief 写字符串到内存文件
// @desc 该函数先将字符串长度写入内存，再将字符串内容写入内存，不包括结束字符
//
extern bool writeMemFileStringW(glMemFile & memFile, const glStringW & string);

//
// @brief 从内存文件读取字符串
// @desc 该函数先从内存读取字符串长度，再从内存读取字符串，最后在字符串末尾追加结束字符
//
extern bool readMemFileStringW(glMemFile & memFile, glStringW & string);

//
// @brief 计算指定字符串写入到内存后需要多少字节空间
// @desc 字符串写入到内存后，内存中应包含字符串长度以及字符串内容，不包含结束字符
//
extern int calcMemStringSizeW(const glStringW & string);

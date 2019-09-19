
#pragma once

//
// @brief 不可复制基类
//
class glNonCopyable {
public:
	glNonCopyable();
	virtual ~glNonCopyable();
private:
	//
	// @brief 禁用拷贝构造函数
	//
	glNonCopyable(const glNonCopyable & other);
	//
	// @brief 禁用赋值运算符
	//
	glNonCopyable & operator = (const glNonCopyable & other);
};

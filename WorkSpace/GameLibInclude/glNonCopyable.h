
#pragma once

//
// @brief ���ɸ��ƻ���
//
class glNonCopyable {
public:
	glNonCopyable();
	virtual ~glNonCopyable();
private:
	glNonCopyable(const glNonCopyable & other);
	glNonCopyable & operator = (const glNonCopyable & other);
};


#pragma once

//
// @brief ���ɸ��ƻ���
//
class glNonCopyable {
public:
	glNonCopyable();
	virtual ~glNonCopyable();
private:
	//
	// @brief ���ÿ������캯��
	//
	glNonCopyable(const glNonCopyable & other);
	//
	// @brief ���ø�ֵ�����
	//
	glNonCopyable & operator = (const glNonCopyable & other);
};


#pragma once

//
// @brief ͼԪ����ö����
//
enum glPrimitiveType {
	// δ֪
	glPrimitiveTypeUnknown,
	// ��
	glPrimitiveTypePoint,
	// �߶�
	glPrimitiveTypeLine,
	// ʵ��������
	glPrimitiveTypeTriangle,
};

//
// @brief ��������ö����
//
enum glInputType {
	// ��������
	glInputTypeKeyDown,
	// ��������
	glInputTypeKeyUp,
	// ����ƶ�
	glInputTypeMouseMove,
};

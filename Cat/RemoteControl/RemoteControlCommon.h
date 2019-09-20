
#pragma once

//
// Զ�̿���ϵͳ����ͷ�ļ�
//

//
// @brief Э��ö����
// @desc
//
// һ��Э�飬�ȼ���һ�����͵��������ݰ������ڲ�ͬЭ�����͵��������ݰ�
// ���������ݵĴ���ʽ������ͬ
//
enum {
	// �ڱ�
	PROTOCOL_FIRST,
	// �ͻ��������������û�����
	PROTOCOL_REQUEST_USER_NAME,
	// �������ͻ�����Ӧ�û�����
	PROTOCOL_RESPONSE_USER_NAME,
	// �ڱ�
	PROTOCOL_LAST,
};

//
// @brief �������ݰ�ͷ
// @desc
//
// ͨ����һ���������������ݰ����ڴ�ģ�����£�
//
// |------------------------|
// | ��ͷ�����룩             |
// |------------------------|
// | ���壨��ѡ��             |
// |------------------------|
//
// ��ͷ�� SPackHeader �ṹ�������������С�ɰ�ͷ�ṹ��� mPackSize �ֶ�����
// ���ݲ�ͬ��Э�飬��������ݲ�����ͬ�����磺���ڿͻ��������������û���ʱ������Ҫ
// �������壬���������ͻ�����Ӧ�û�������ʱ����������û����ַ������Դ����ơ�
//
struct SPackHeader {
	// ��ǩ��
	unsigned char mSig[4];
	// ���汾��
	unsigned short int mVerMajor = 0;
	// ���汾��
	unsigned short int mVerMinor = 0;
	// �������ݴ�С����������ͷ
	unsigned short int mPackSize = 0;
	// Э������
	unsigned short int mProtocol = PROTOCOL_FIRST;
};

//
// @brief �������ݰ�
//
struct SPack : public SPackHeader {
	// ��������
	// ���ݲ�ͬ��Э�����ͣ��������������������ݸ���
	void * mData;
};

//
// @brief ��֤���ݰ��Ƿ���Ч
//
extern bool isPackValid(const SPackHeader & packHeader);

//
// @brief ������ݰ���ͷ
//
extern void makePackHeader(SPackHeader & packHeader, const int protocol);

//
// @brief д�ַ������ڴ��ļ�
// @desc �ú����Ƚ��ַ�������д���ڴ棬�ٽ��ַ�������д���ڴ棬�����������ַ�
//
extern bool writeMemFileStringW(glMemFile & memFile, const glStringW & string);

//
// @brief ���ڴ��ļ���ȡ�ַ���
// @desc �ú����ȴ��ڴ��ȡ�ַ������ȣ��ٴ��ڴ��ȡ�ַ�����������ַ���ĩβ׷�ӽ����ַ�
//
extern bool readMemFileStringW(glMemFile & memFile, glStringW & string);

//
// @brief ����ָ���ַ���д�뵽�ڴ����Ҫ�����ֽڿռ�
// @desc �ַ���д�뵽�ڴ���ڴ���Ӧ�����ַ��������Լ��ַ������ݣ������������ַ�
//
extern int calcMemStringSizeW(const glStringW & string);

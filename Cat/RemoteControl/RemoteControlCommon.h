
#pragma once

//
// Զ�̿���ϵͳ����ͷ�ļ�
//

// ����˼��� ip ��ַ
#define REMOTE_CONTROL_IP ("127.0.0.1")
// ����˼����˿�
#define REMOTE_CONTROL_PORT (10086)
// ��ǩ��
#define PACK_SIG ("PACK")
// ���汾��
#define PACK_VER_MAJOR (0)
// ���汾��
#define PACK_VER_MINOR (1)

//
// Э��ö����
//
// һ��Э�飬�൱��һ�����͵���������
//
enum
{
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
// �������ݰ�ͷ
//
struct SPackHeader
{
	// ��ǩ��
	unsigned char mSig[4];
	// ���汾��
	unsigned short int mVerMajor = 0;
	// ���汾��
	unsigned short int mVerMinor = 0;
	// �������ݴ�С
	unsigned short int mPackSize = 0;
	// Э������
	unsigned short int mProtocol = PROTOCOL_FIRST;
};

//
// �������ݰ�
//
struct SPack : public SPackHeader
{
	// ��������
	// ���ݲ�ͬ��Э�����ͣ��������������������ݸ���
	void * mData;
};

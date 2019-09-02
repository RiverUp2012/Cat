
#pragma once

//
// �ڴ�д����
//
class CMemoryWriter
{
public:

	CMemoryWriter();
	virtual ~CMemoryWriter();

public:

	//
	// ���ڴ�飬�Ժ�Ĳ���������Ը��ڴ��
	//
	void bind(void * buffer, const int bufferSize);

	//
	// ���ڴ��д������
	//
	void write(const void * value, const int valueSize);

	template <typename _U>
	void write(_U * value)
	{
		write(value, sizeof(_U));
	}

private:

	unsigned char * mBuffer = 0;
	int mBufferSize = 0;
	int mPointer = 0;
};

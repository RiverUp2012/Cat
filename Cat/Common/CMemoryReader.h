
#pragma once

//
// �ڴ��ȡ��
//
class CMemoryReader
{
public:

	CMemoryReader();
	virtual ~CMemoryReader();

public:

	//
	// ���ڴ�飬�Ժ�Ĳ���������Ը��ڴ��
	//
	void bind(void * buffer, const int bufferSize);

	//
	// ���ڴ���ȡ����
	//
	void read(void * value, const int valueSize);
	
	template <typename _U>
	void read(_U * value)
	{
		read(value, sizeof(_U));
	}

private:

	unsigned char * mBuffer = 0;
	int mBufferSize = 0;
	int mPointer = 0;
};

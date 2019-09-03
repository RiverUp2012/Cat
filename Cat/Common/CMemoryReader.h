
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
	bool read(void * value, const int valueSize);
	
	//
	// ���ڴ���ȡ����
	//
	// ��ο� CMemoryWriter �� write<_U>() ģ�巽��
	//
	template <typename _U>
	bool read(_U * value)
	{
		return read(value, sizeof(_U));
	}

	//
	// ��ȡ��ȡָ��
	//
	int getPointer(void) const;

private:

	unsigned char * mBuffer = 0;
	int mBufferSize = 0;
	int mPointer = 0; // ��ȡָ�룬ָ���ڴ������һ�εĲ���λ��
};

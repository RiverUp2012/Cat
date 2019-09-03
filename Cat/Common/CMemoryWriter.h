
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
	bool write(const void * value, const int valueSize);

	//
	// ���ڴ��д������
	//
	// �÷�����һ��ģ�巽���������ñ������Զ��Ʋ�Ҫд������ݵĴ�С������������ȷ������
	// ���������Զ�Ϊ�����Ʋ�����ݴ�С�����磺
	//
	// CMemoryWriter memWriter;
	// int value = 0;
	//
	// memWriter.write(&value); // �������Զ�ʶ��� value Ϊ int ���ͣ����������ݴ�СΪ sizeof(int)
	//
	template <typename _U>
	bool write(_U * value)
	{
		return write(value, sizeof(_U));
	}

	//
	// ��ȡд��ָ��
	//
	int getPointer(void) const;

private:

	unsigned char * mBuffer = 0;
	int mBufferSize = 0;
	int mPointer = 0; // д��ָ�룬ָ���ڴ������һ�εĲ���λ��
};

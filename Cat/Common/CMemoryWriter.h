
#pragma once

//
// 内存写入类
//
class CMemoryWriter
{
public:

	CMemoryWriter();
	virtual ~CMemoryWriter();

public:

	//
	// 绑定内存块，以后的操作都将针对该内存块
	//
	void bind(void * buffer, const int bufferSize);

	//
	// 向内存块写入数据
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

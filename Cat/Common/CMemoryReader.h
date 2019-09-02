
#pragma once

//
// 内存读取类
//
class CMemoryReader
{
public:

	CMemoryReader();
	virtual ~CMemoryReader();

public:

	//
	// 绑定内存块，以后的操作都将针对该内存块
	//
	void bind(void * buffer, const int bufferSize);

	//
	// 从内存块读取数据
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

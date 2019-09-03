
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
	bool read(void * value, const int valueSize);
	
	//
	// 从内存块读取数据
	//
	// 请参考 CMemoryWriter 的 write<_U>() 模板方法
	//
	template <typename _U>
	bool read(_U * value)
	{
		return read(value, sizeof(_U));
	}

	//
	// 获取读取指针
	//
	int getPointer(void) const;

private:

	unsigned char * mBuffer = 0;
	int mBufferSize = 0;
	int mPointer = 0; // 读取指针，指向内存块中下一次的操作位置
};

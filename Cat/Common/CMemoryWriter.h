
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
	bool write(const void * value, const int valueSize);

	//
	// 向内存块写入数据
	//
	// 该方法是一个模板方法，用于让编译器自动推测要写入的数据的大小，对于类型明确的数据
	// 编译器会自动为我们推测出数据大小，比如：
	//
	// CMemoryWriter memWriter;
	// int value = 0;
	//
	// memWriter.write(&value); // 编译器自动识别出 value 为 int 类型，并且其数据大小为 sizeof(int)
	//
	template <typename _U>
	bool write(_U * value)
	{
		return write(value, sizeof(_U));
	}

	//
	// 获取写入指针
	//
	int getPointer(void) const;

private:

	unsigned char * mBuffer = 0;
	int mBufferSize = 0;
	int mPointer = 0; // 写入指针，指向内存块中下一次的操作位置
};

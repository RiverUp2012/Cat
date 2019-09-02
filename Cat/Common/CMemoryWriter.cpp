
#include "stdafx.h"
#include "CMemoryWriter.h"

CMemoryWriter::CMemoryWriter()
{

}

CMemoryWriter::~CMemoryWriter()
{

}

void CMemoryWriter::bind(void * buffer, const int bufferSize)
{
	mBuffer = (unsigned char *)buffer;
	mBufferSize = bufferSize;
	mPointer = 0;
}

void CMemoryWriter::write(const void * value, const int valueSize)
{
	if (mBuffer &&
		mBufferSize > 0 &&
		value &&
		valueSize > 0 &&
		mPointer + valueSize <= mBufferSize)
	{
		memcpy(&(mBuffer[mPointer]), value, valueSize);
		mPointer += valueSize;
	}
}

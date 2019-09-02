
#include "stdafx.h"
#include "CMemoryReader.h"

CMemoryReader::CMemoryReader()
{

}

CMemoryReader::~CMemoryReader()
{

}

void CMemoryReader::bind(void * buffer, const int bufferSize)
{
	mBuffer = (unsigned char *)buffer;
	mBufferSize = bufferSize;
	mPointer = 0;
}

void CMemoryReader::read(void * value, const int valueSize)
{
	if (mBuffer &&
		mBufferSize > 0 &&
		value &&
		valueSize > 0 &&
		mPointer + valueSize <= mBufferSize)
	{
		memcpy(value, &(mBuffer[mPointer]), valueSize);
		mPointer += valueSize;
	}
}

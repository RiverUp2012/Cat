
#pragma once

#include "glNonCopyable.h"
#include "glFile.h"
#include "glMemFile.h"

//
// @brief wave 读取类
//
class glWaveReader : public glNonCopyable {
public:
	glWaveReader();
	virtual ~glWaveReader();
public:
	//
	// @brief 从文件读取
	//
	bool createFromFileW(const wchar_t * fileName);
	//
	// @brief 从内存读取
	//
	bool createFromMemory(const void * buffer, const int bufferSize, const bool autoDelete);
	//
	// @brief 从模块资源读取
	//
	bool createFromResourceW(const int resourceID, const wchar_t * resourceType);
	void destroy(void);
	unsigned short getChannels(void) const;
	unsigned short getBitsPerSample(void) const;
	unsigned int getSampleRate(void) const;
	unsigned int getPCMDataSize(void) const;
	bool readAllPCMData(void * buffer);
private:
	glFile mWaveFile;
	glMemFile mMemWavFile;
	unsigned short mChannels;
	unsigned short mBitsPerSample;
	unsigned int mSampleRate;
	long long int mPCMDataOffset;
	unsigned int mPCMDataSize;
};

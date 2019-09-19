
#pragma once

#include "glNonCopyable.h"
#include "glFile.h"

//
// @brief wave ∂¡»°¿‡
//
class glWaveReader : public glNonCopyable {
public:
	glWaveReader();
	virtual ~glWaveReader();
public:
	bool createFromFileW(const wchar_t * fileName);
	bool createFromMemory(const void * buffer, const int bufferSize);
	void destroy(void);
	unsigned short getChannels(void) const;
	unsigned short getBitsPerSample(void) const;
	unsigned int getSampleRate(void) const;
	unsigned int getPCMDataSize(void) const;
	bool readAllPCMData(void * buffer);
private:
	glFile mWaveFile;
	unsigned short mChannels;
	unsigned short mBitsPerSample;
	unsigned int mSampleRate;
	long long int mPCMDataOffset;
	unsigned int mPCMDataSize;
};

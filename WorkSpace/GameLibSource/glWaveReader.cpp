
#include "../GameLibInclude/glWaveReader.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glTemplate.h"

struct glWaveChunkHeader {
	unsigned char mSig[4];
	unsigned int mSize;
};

glWaveReader::glWaveReader() {
	mChannels = 0;
	mBitsPerSample = 0;
	mSampleRate = 0;
	mPCMDataOffset = 0;
	mPCMDataSize = 0;
}

glWaveReader::~glWaveReader() {
	destroy();
}

bool glWaveReader::createFromFileW(const wchar_t * fileName) {
	bool ret = false;
	glWaveChunkHeader chkHdr = { 0 };
	WAVEFORMATEX wavFmt = { 0 };
	destroy();
	if (fileName && mWaveFile.openW(fileName, true, false)) {
		if (glReadFile(mWaveFile, chkHdr) &&
			0 == memcmp("RIFF", chkHdr.mSig, 4) &&
			glReadFile(mWaveFile, chkHdr.mSig) &&
			0 == memcmp("WAVE", chkHdr.mSig, 4)) {
			if (glReadFile(mWaveFile, chkHdr) &&
				0 == memcmp("fmt ", chkHdr.mSig, 4) &&
				chkHdr.mSize <= sizeof(wavFmt) &&
				mWaveFile.read(&wavFmt, chkHdr.mSize)) {
				mChannels = wavFmt.nChannels;
				mBitsPerSample = wavFmt.wBitsPerSample;
				mSampleRate = wavFmt.nSamplesPerSec;
				while (true) {
					if (glReadFile(mWaveFile, chkHdr)) {
						if (0 == memcmp("data", chkHdr.mSig, 4)) {
							if (mWaveFile.getPointer(mPCMDataOffset)) {
								mPCMDataSize = chkHdr.mSize;
								ret = true;
							}
							break;
						}
						else {
							if (!mWaveFile.seekOffset(chkHdr.mSize)) {
								break;
							}
						}
					}
					else {
						break;
					}
				}
			}
		}
	}
	if (!ret) {
		destroy();
	}
	return ret;
}

bool glWaveReader::createFromMemory(const void * buffer, const int bufferSize) {
	bool ret = false;
	glWaveChunkHeader chkHdr = { 0 };
	WAVEFORMATEX wavFmt = { 0 };
	destroy();
	if (buffer && bufferSize > 0) {
		// todo
	}
	if (!ret) {
		destroy();
	}
	return ret;
}

void glWaveReader::destroy(void) {
	mWaveFile.close();
	mChannels = 0;
	mBitsPerSample = 0;
	mSampleRate = 0;
	mPCMDataOffset = 0;
	mPCMDataSize = 0;
}

unsigned short glWaveReader::getChannels(void) const {
	return mChannels;
}

unsigned short glWaveReader::getBitsPerSample(void) const {
	return mBitsPerSample;
}

unsigned int glWaveReader::getSampleRate(void) const {
	return mSampleRate;
}

unsigned int glWaveReader::getPCMDataSize(void) const {
	return mPCMDataSize;
}

bool glWaveReader::readAllPCMData(void * buffer) {
	if (mWaveFile.isAlready() && buffer && mPCMDataSize > 0) {
		if (mWaveFile.seekTo(mPCMDataOffset)) {
			if (mWaveFile.read(buffer, mPCMDataSize)) {
				return true;
			}
		}
	}
	return false;
}

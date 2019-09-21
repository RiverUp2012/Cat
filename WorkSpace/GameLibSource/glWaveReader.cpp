
#include "../GameLibInclude/glWaveReader.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glTemplate.h"
#include "../GameLibInclude/glModuleResourceHelper.h"

namespace {
	struct glWaveChunkHeader {
		unsigned char mSig[4];
		unsigned int mSize;
	};
}

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
				for (;;) {
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

bool glWaveReader::createFromMemory(const void * buffer, const int bufferSize, const bool autoDelete) {
	bool ret = false;
	glWaveChunkHeader chkHdr = { 0 };
	WAVEFORMATEX wavFmt = { 0 };
	int filePointer = 0;
	destroy();
	if (buffer && bufferSize) {
		mMemWavFile.open(buffer, bufferSize, autoDelete);
		if (glReadMemFile(mMemWavFile, chkHdr) &&
			0 == memcmp("RIFF", chkHdr.mSig, 4) &&
			glReadMemFile(mMemWavFile, chkHdr.mSig) &&
			0 == memcmp("WAVE", chkHdr.mSig, 4)) {
			if (glReadMemFile(mMemWavFile, chkHdr) &&
				0 == memcmp("fmt ", chkHdr.mSig, 4) &&
				chkHdr.mSize <= sizeof(wavFmt) &&
				mMemWavFile.read(&wavFmt, chkHdr.mSize)) {
				mChannels = wavFmt.nChannels;
				mBitsPerSample = wavFmt.wBitsPerSample;
				mSampleRate = wavFmt.nSamplesPerSec;
				for (;;) {
					if (glReadMemFile(mMemWavFile, chkHdr)) {
						if (0 == memcmp("data", chkHdr.mSig, 4)) {
							if (mMemWavFile.getPointer(filePointer)) {
								mPCMDataOffset = filePointer;
								mPCMDataSize = chkHdr.mSize;
								ret = true;
							}
							break;
						}
						else {
							if (!mMemWavFile.seekOffset(chkHdr.mSize)) {
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

bool glWaveReader::createFromResourceW(const int resourceID, const wchar_t * resourceType) {
	glModuleResourceHelper::glResourceInfo resInfo;
	if (resourceType) {
		if (glModuleResourceHelper::getResourceW(resourceID, resourceType, resInfo)) {
			return createFromMemory(resInfo.mData, resInfo.mSize, false);
		}
	}
	return false;
}

void glWaveReader::destroy(void) {
	mWaveFile.close();
	mMemWavFile.close();
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
	if (buffer && mPCMDataSize > 0) {
		if (mWaveFile.isAlready()) {
			if (mWaveFile.seekTo(mPCMDataOffset)) {
				if (mWaveFile.read(buffer, mPCMDataSize)) {
					return true;
				}
			}
		}
		else if (mMemWavFile.isAlready()) {
			if (mMemWavFile.seekTo(static_cast<int>(mPCMDataOffset))) {
				if (mMemWavFile.read(buffer, mPCMDataSize)) {
					return true;
				}
			}
		}
	}
	return false;
}

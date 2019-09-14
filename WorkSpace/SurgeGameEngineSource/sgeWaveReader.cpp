
#include "../SurgeGameEngine.h"
#include "../Include/SurgeGameEnginePrivate.h"

struct sgeWaveChunkHeader
{
	unsigned char mSig[4];
	unsigned int mSize;
};

sgeWaveReader::sgeWaveReader()
{
	mChannels = 0;
	mBitsPerSample = 0;
	mSampleRate = 0;
	mPCMDataOffset = 0;
	mPCMDataSize = 0;
}

sgeWaveReader::~sgeWaveReader()
{
	destroy();
}

bool sgeWaveReader::createFromFileW(const wchar_t * fileName)
{
	bool ret = false;
	sgeWaveChunkHeader chkHdr = { 0 };
	WAVEFORMATEX wavFmt = { 0 };

	destroy();

	if (fileName && mWaveFile.openW(fileName, true, false))
	{
		if (sgeReadFile(mWaveFile, chkHdr) &&
			0 == memcmp("RIFF", chkHdr.mSig, 4) &&
			sgeReadFile(mWaveFile, chkHdr.mSig) &&
			0 == memcmp("WAVE", chkHdr.mSig, 4))
		{
			if (sgeReadFile(mWaveFile, chkHdr) &&
				0 == memcmp("fmt ", chkHdr.mSig, 4) &&
				chkHdr.mSize <= sizeof(wavFmt) &&
				mWaveFile.read(&wavFmt, chkHdr.mSize))
			{
				mChannels = wavFmt.nChannels;
				mBitsPerSample = wavFmt.wBitsPerSample;
				mSampleRate = wavFmt.nSamplesPerSec;

				while (true)
				{
					if (sgeReadFile(mWaveFile, chkHdr))
					{
						if (0 == memcmp("data", chkHdr.mSig, 4))
						{
							if (mWaveFile.getPointer(mPCMDataOffset))
							{
								mPCMDataSize = chkHdr.mSize;

								ret = true;
							}

							break;
						}
						else
						{
							if (!mWaveFile.seekOffset(chkHdr.mSize))
							{
								break;
							}
						}
					}
					else
					{
						break;
					}
				}
			}
		}
	}

	if (!ret)
	{
		destroy();
	}

	return ret;
}

void sgeWaveReader::destroy(void)
{
	mWaveFile.close();
	mChannels = 0;
	mBitsPerSample = 0;
	mSampleRate = 0;
	mPCMDataOffset = 0;
	mPCMDataSize = 0;
}

unsigned short sgeWaveReader::getChannels(void) const
{
	return mChannels;
}

unsigned short sgeWaveReader::getBitsPerSample(void) const
{
	return mBitsPerSample;
}

unsigned int sgeWaveReader::getSampleRate(void) const
{
	return mSampleRate;
}

unsigned int sgeWaveReader::getPCMDataSize(void) const
{
	return mPCMDataSize;
}

bool sgeWaveReader::readAllPCMData(void * buffer)
{
	if (mWaveFile.isAlready() && buffer && mPCMDataSize > 0)
	{
		if (mWaveFile.seekTo(mPCMDataOffset))
		{
			if (mWaveFile.read(buffer, mPCMDataSize))
			{
				return true;
			}
		}
	}

	return false;
}

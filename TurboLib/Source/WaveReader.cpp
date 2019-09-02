
#include "../TurboLib.h"
#include "../Include/Private.h"

#define T_MAX_WAVEREADER (32)

typedef struct _T_WAVECHUNK
{
	unsigned char mSig[4];
	unsigned int mSize;
}
T_WAVECHUNK;

typedef struct _T_WAVEREADER
{
	T_OBJECT mWaveFile;
	unsigned char * mWaveStream;
	unsigned short mChannels;
	unsigned short mBitsPerSample;
	unsigned int mSampleRate;
	long long int mPCMDataOffset;
	int mPCMDataSize;
}
T_WAVEREADER;

static T_WAVEREADER gWaveReaderArray[T_MAX_WAVEREADER] = { 0 };

static T_WAVEREADER * TFindUnuseWaveReader(void)
{
	for (int i = 0; i < T_MAX_WAVEREADER; ++i)
	{
		if (!gWaveReaderArray[i].mWaveFile &&
			!gWaveReaderArray[i].mWaveStream)
		{
			return &gWaveReaderArray[i];
		}
	}

	return 0;
}

T_OBJECT TWaveReaderCreateFromWaveFileW(
	const wchar_t * waveFileName)
{
	T_WAVECHUNK waveChunk = { 0 };
	WAVEFORMATEX waveFmt = { 0 };

	T_WAVEREADER * waveReaderImpl = TFindUnuseWaveReader();
	if (waveReaderImpl)
	{
		waveReaderImpl->mWaveFile = TFileOpenW(waveFileName, T_TRUE, T_FALSE);
		if (waveReaderImpl->mWaveFile)
		{
			if (TFileRead(waveReaderImpl->mWaveFile, &waveChunk, sizeof(waveChunk)) &&
				0 == memcmp("RIFF", waveChunk.mSig, 4) &&
				TFileRead(waveReaderImpl->mWaveFile, &waveChunk.mSig, sizeof(waveChunk.mSig)) &&
				0 == memcmp("WAVE", waveChunk.mSig, 4))
			{
				if (TFileRead(waveReaderImpl->mWaveFile, &waveChunk, sizeof(waveChunk)) &&
					0 == memcmp("fmt ", waveChunk.mSig, 4) &&
					waveChunk.mSize <= sizeof(waveFmt) &&
					TFileRead(waveReaderImpl->mWaveFile, &waveFmt, waveChunk.mSize))
				{
					for (;;)
					{
						if (TFileRead(waveReaderImpl->mWaveFile, &waveChunk, sizeof(waveChunk)))
						{
							if (0 == memcmp("data", waveChunk.mSig, 4))
							{
								waveReaderImpl->mChannels = waveFmt.nChannels;
								waveReaderImpl->mBitsPerSample = waveFmt.wBitsPerSample;
								waveReaderImpl->mSampleRate = waveFmt.nSamplesPerSec;
								TFileGetPointer(waveReaderImpl->mWaveFile, &waveReaderImpl->mPCMDataOffset);
								waveReaderImpl->mPCMDataSize = waveChunk.mSize;

								return (T_OBJECT)waveReaderImpl;
							}
							else
							{
								if (!TFileSeekOffset(waveReaderImpl->mWaveFile, waveChunk.mSize))
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

			TFileClose(waveReaderImpl->mWaveFile);
			waveReaderImpl->mWaveFile = 0;
		}
	}

	return 0;
}

void TWaveReaderDestroy(
	T_OBJECT waveReader)
{
	T_WAVEREADER * waveReaderImpl = (T_WAVEREADER *)waveReader;
	if (waveReaderImpl)
	{
		if (waveReaderImpl->mWaveFile)
		{
			TFileClose(waveReaderImpl->mWaveFile);
			waveReaderImpl->mWaveFile = 0;
		}

		TMemset(waveReaderImpl, sizeof(T_WAVEREADER), 0);
	}
}

void TWaveReaderGetPCMParam(
	T_OBJECT waveReader,
	int * pcmDataSize,
	unsigned short * channels,
	unsigned short * bitsPerSample,
	unsigned int * sampleRate)
{
	T_WAVEREADER * waveReaderImpl = (T_WAVEREADER *)waveReader;
	if (waveReaderImpl)
	{
		if (pcmDataSize)
		{
			*pcmDataSize = waveReaderImpl->mPCMDataSize;
		}

		if (channels)
		{
			*channels = waveReaderImpl->mChannels;
		}

		if (bitsPerSample)
		{
			*bitsPerSample = waveReaderImpl->mBitsPerSample;
		}

		if (sampleRate)
		{
			*sampleRate = waveReaderImpl->mSampleRate;
		}
	}
}

int TWaveReaderReadPCMData(
	T_OBJECT waveReader,
	void * buffer,
	const int bytesToRead)
{
	T_WAVEREADER * waveReaderImpl = (T_WAVEREADER *)waveReader;
	if (waveReaderImpl && buffer && bytesToRead > 0)
	{
		if (waveReaderImpl->mWaveFile)
		{
			if (TFileSeekTo(waveReaderImpl->mWaveFile, waveReaderImpl->mPCMDataOffset))
			{
				if (TFileRead(waveReaderImpl->mWaveFile, buffer, bytesToRead))
				{
					return T_TRUE;
				}
			}
		}
		else if (waveReaderImpl->mWaveStream)
		{
			memcpy(
				&(waveReaderImpl->mWaveStream[waveReaderImpl->mPCMDataOffset]),
				buffer,
				bytesToRead);

			return T_TRUE;
		}
	}

	return T_FALSE;
}


#include "../Include/Private.h"
#include "../Include/DS8Common.h"
#include "../Include/CompileConfig.h"
#include "../Include/WaveReader.h"

#if defined T_USE_DS8

#define T_MAX_DS8SOUNDBUFFER (32)

typedef struct _T_DS8SOUNDBUFFER
{
	struct IDirectSoundBuffer8 * mDSBuf8;
	void * mAudioBufferLocked;
	DWORD mAudioBufferSizeLocked;
}
T_DS8SOUNDBUFFER;

static T_DS8SOUNDBUFFER gDS8SoundBufferArray[T_MAX_DS8SOUNDBUFFER] = { 0 };

static T_DS8SOUNDBUFFER * TFindUnuseDS8SoundBuffer(void)
{
	for (int i = 0; i < T_MAX_DS8SOUNDBUFFER; ++i)
	{
		if (!gDS8SoundBufferArray[i].mDSBuf8)
		{
			return &gDS8SoundBufferArray[i];
		}
	}

	return 0;
}

#endif // T_USE_DS8

T_OBJECT TDS8SoundBufferCreate(
	T_OBJECT ds8SoundDevice,
	const unsigned int bufferSize,
	const unsigned short channels,
	const unsigned short bitsPerSample,
	const unsigned int sampleRate)
{
#if defined T_USE_DS8

	DSBUFFERDESC dsBufDesc = { 0 };
	WAVEFORMATEX wavFmt = { 0 };
	struct IDirectSoundBuffer * dsBuf = 0;
	int done = T_FALSE;

	struct IDirectSound8 * ds8 = TDS8SoundDeviceGetIDirectSound8(ds8SoundDevice);
	T_DS8SOUNDBUFFER * ds8SoundBufferImpl = TFindUnuseDS8SoundBuffer();
	if (ds8 && ds8SoundBufferImpl)
	{
		wavFmt.wFormatTag = WAVE_FORMAT_PCM;
		wavFmt.nChannels = channels;
		wavFmt.wBitsPerSample = bitsPerSample;
		wavFmt.nSamplesPerSec = sampleRate;
		wavFmt.nBlockAlign = wavFmt.nChannels * wavFmt.wBitsPerSample / 8;
		wavFmt.nAvgBytesPerSec = wavFmt.nBlockAlign * wavFmt.nSamplesPerSec;

		dsBufDesc.dwSize = sizeof(dsBufDesc);
		dsBufDesc.dwBufferBytes = bufferSize;
		dsBufDesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLVOLUME;
		dsBufDesc.lpwfxFormat = &wavFmt;

		if (SUCCEEDED(ds8->CreateSoundBuffer(
			&dsBufDesc,
			&dsBuf,
			0)))
		{
			if (SUCCEEDED(dsBuf->QueryInterface(
				IID_IDirectSoundBuffer8,
				(LPVOID *)&ds8SoundBufferImpl->mDSBuf8)))
			{
				done = T_TRUE;
			}

			dsBuf->Release();
			dsBuf = 0;
		}

		if (!done)
		{
			if (ds8SoundBufferImpl->mDSBuf8)
			{
				ds8SoundBufferImpl->mDSBuf8->Release();
				ds8SoundBufferImpl->mDSBuf8 = 0;
			}

			ds8SoundBufferImpl = 0;
		}
	}

	return (T_OBJECT)ds8SoundBufferImpl;

#endif // T_USE_DS8

	return 0;
}

T_OBJECT TDS8SoundBufferCreateFromWaveFileW(
	T_OBJECT ds8SoundDevice,
	const wchar_t * waveFileName)
{
	T_OBJECT ds8SoundBuffer = 0;
	T_OBJECT waveReader = 0;
	unsigned short channels = 0;
	unsigned short bitsPerSample = 0;
	unsigned int sampleRate = 0;
	int pcmDataSize = 0;
	void * audioBuffer = 0;
	int done = T_FALSE;

	waveReader = TWaveReaderCreateFromWaveFileW(waveFileName);
	if (waveReader)
	{
		TWaveReaderGetPCMParam(
			waveReader,
			&pcmDataSize,
			&channels,
			&bitsPerSample,
			&sampleRate);

		ds8SoundBuffer = TDS8SoundBufferCreate(
			ds8SoundDevice,
			pcmDataSize,
			channels,
			bitsPerSample,
			sampleRate);
		if (ds8SoundBuffer)
		{
			audioBuffer = TDS8SoundBufferLock(ds8SoundBuffer, 0, pcmDataSize);
			if (audioBuffer)
			{
				if (TWaveReaderReadPCMData(waveReader, audioBuffer, pcmDataSize))
				{
					if (TDS8SoundBufferUnlock(ds8SoundBuffer))
					{
						done = T_TRUE;
					}
				}
			}

			if (!done)
			{
				TDS8SoundBufferDestroy(ds8SoundBuffer);
				ds8SoundBuffer = 0;
			}
		}

		TWaveReaderDestroy(waveReader);
		waveReader = 0;
	}

	return ds8SoundBuffer;
}

void TDS8SoundBufferDestroy(
	T_OBJECT ds8SoundBuffer)
{
#if defined T_USE_DS8

	T_DS8SOUNDBUFFER * ds8SoundBufferImpl = (T_DS8SOUNDBUFFER *)ds8SoundBuffer;
	if (ds8SoundBufferImpl)
	{
		if (ds8SoundBufferImpl->mDSBuf8)
		{
			ds8SoundBufferImpl->mDSBuf8->Release();
			ds8SoundBufferImpl->mDSBuf8 = 0;
		}

		ds8SoundBufferImpl->mAudioBufferLocked = 0;
		ds8SoundBufferImpl->mAudioBufferSizeLocked = 0;
	}

#endif // T_USE_DS8
}

int TDS8SoundBufferPlay(
	T_OBJECT ds8SoundBuffer,
	const int loop)
{
#if defined T_USE_DS8

	T_DS8SOUNDBUFFER * ds8SoundBufferImpl = (T_DS8SOUNDBUFFER *)ds8SoundBuffer;
	if (ds8SoundBufferImpl && ds8SoundBufferImpl->mDSBuf8)
	{
		if (SUCCEEDED(ds8SoundBufferImpl->mDSBuf8->Play(
			0,
			0,
			(loop ? DSBPLAY_LOOPING : 0))))
		{
			return T_TRUE;
		}
	}

#endif // T_USE_DS8

	return T_FALSE;
}

int TDS8SoundBufferStop(
	T_OBJECT ds8SoundBuffer)
{
#if defined T_USE_DS8

	T_DS8SOUNDBUFFER * ds8SoundBufferImpl = (T_DS8SOUNDBUFFER *)ds8SoundBuffer;
	if (ds8SoundBufferImpl && ds8SoundBufferImpl->mDSBuf8)
	{
		if (SUCCEEDED(ds8SoundBufferImpl->mDSBuf8->Stop()))
		{
			return T_TRUE;
		}
	}

#endif // T_USE_DS8

	return T_FALSE;
}

int TDS8SoundBufferSetVolume(
	T_OBJECT ds8SoundBuffer,
	const float volume)
{
#if defined T_USE_DS8

	T_DS8SOUNDBUFFER * ds8SoundBufferImpl = (T_DS8SOUNDBUFFER *)ds8SoundBuffer;
	if (ds8SoundBufferImpl && ds8SoundBufferImpl->mDSBuf8)
	{
		if (SUCCEEDED(ds8SoundBufferImpl->mDSBuf8->SetVolume(
			TDS8LibVolumeToDS8Volume(volume))))
		{
			return T_TRUE;
		}
	}

#endif // T_USE_DS8

	return T_FALSE;
}

int TDS8SoundBufferGetVolume(
	T_OBJECT ds8SoundBuffer,
	float * volume)
{
#if defined T_USE_DS8

	LONG ds8Volume = 0;

	T_DS8SOUNDBUFFER * ds8SoundBufferImpl = (T_DS8SOUNDBUFFER *)ds8SoundBuffer;
	if (ds8SoundBufferImpl && ds8SoundBufferImpl->mDSBuf8 && volume)
	{
		if (SUCCEEDED(ds8SoundBufferImpl->mDSBuf8->GetVolume(
			&ds8Volume)))
		{
			*volume = TDS8DS8VolumeToLibVolume(ds8Volume);

			return T_TRUE;
		}
	}

#endif // T_USE_DS8

	return T_FALSE;
}

void * TDS8SoundBufferLock(
	T_OBJECT ds8SoundBuffer,
	const int offsetToLock,
	const int bytesToLock)
{
#if defined T_USE_DS8

	T_DS8SOUNDBUFFER * ds8SoundBufferImpl = (T_DS8SOUNDBUFFER *)ds8SoundBuffer;
	if (ds8SoundBufferImpl &&
		ds8SoundBufferImpl->mDSBuf8 &&
		!ds8SoundBufferImpl->mAudioBufferLocked &&
		!ds8SoundBufferImpl->mAudioBufferSizeLocked)
	{
		if (SUCCEEDED(ds8SoundBufferImpl->mDSBuf8->Lock(
			offsetToLock,
			bytesToLock,
			&ds8SoundBufferImpl->mAudioBufferLocked,
			&ds8SoundBufferImpl->mAudioBufferSizeLocked,
			0,
			0,
			0)))
		{
			return ds8SoundBufferImpl->mAudioBufferLocked;
		}
	}

#endif // T_USE_DS8

	return 0;
}

int TDS8SoundBufferUnlock(
	T_OBJECT ds8SoundBuffer)
{
#if defined T_USE_DS8

	T_DS8SOUNDBUFFER * ds8SoundBufferImpl = (T_DS8SOUNDBUFFER *)ds8SoundBuffer;
	if (ds8SoundBufferImpl &&
		ds8SoundBufferImpl->mDSBuf8 &&
		ds8SoundBufferImpl->mAudioBufferLocked &&
		ds8SoundBufferImpl->mAudioBufferSizeLocked)
	{
		if (SUCCEEDED(ds8SoundBufferImpl->mDSBuf8->Unlock(
			ds8SoundBufferImpl->mAudioBufferLocked,
			ds8SoundBufferImpl->mAudioBufferSizeLocked,
			0,
			0)))
		{
			ds8SoundBufferImpl->mAudioBufferLocked = 0;
			ds8SoundBufferImpl->mAudioBufferSizeLocked = 0;

			return T_TRUE;
		}
	}

#endif // T_USE_DS8

	return T_FALSE;
}

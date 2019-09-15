
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

glSound::glSound()
{
	mDSBuf8 = 0;
}

glSound::~glSound()
{
	destroy();
}

bool glSound::createFromWaveFileW(const wchar_t * fileName)
{
	bool ret = false;
	glWaveReader wavReader;
	unsigned short channels = 0;
	unsigned short bitsPerSample = 0;
	unsigned int sampleRate = 0;
	unsigned int bufferSize = 0;
	void * audioBuffer = 0;

	destroy();

	if (wavReader.createFromFileW(fileName))
	{
		channels = wavReader.getChannels();
		bitsPerSample = wavReader.getBitsPerSample();
		sampleRate = wavReader.getSampleRate();
		bufferSize = wavReader.getPCMDataSize();

		if (create(channels, bitsPerSample, sampleRate, bufferSize))
		{
			audioBuffer = lock(0, bufferSize);
			if (audioBuffer)
			{
				if (wavReader.readAllPCMData(audioBuffer))
				{
					if (unlock(audioBuffer, bufferSize))
					{
						ret = true;
					}
				}
			}
		}

		wavReader.destroy();
	}

	if (!ret)
	{
		destroy();
	}

	return ret;
}

bool glSound::create(
	const unsigned short channels,
	const unsigned short bitsPerSample,
	const unsigned int sampleRate,
	const unsigned int bufferSize)
{
	bool ret = false;
	DSBUFFERDESC dsBufDesc = { 0 };
	WAVEFORMATEX wavFmt = { 0 };
	IDirectSoundBuffer * dsBuf = 0;

	destroy();

	IDirectSound * ds8 = gSoundDevice.getIDirectSound8();
	if (ds8 && channels && bitsPerSample && sampleRate && bufferSize)
	{
		wavFmt.wFormatTag = WAVE_FORMAT_PCM;
		wavFmt.nChannels = channels;
		wavFmt.nSamplesPerSec = sampleRate;
		wavFmt.wBitsPerSample = bitsPerSample;
		wavFmt.nBlockAlign = wavFmt.nChannels * wavFmt.wBitsPerSample / 8;
		wavFmt.nAvgBytesPerSec = wavFmt.nBlockAlign * wavFmt.nSamplesPerSec;

		dsBufDesc.dwSize = sizeof(dsBufDesc);
		dsBufDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
		dsBufDesc.lpwfxFormat = &wavFmt;

		if (SUCCEEDED(ds8->CreateSoundBuffer(&dsBufDesc, &dsBuf, 0)))
		{
			if (SUCCEEDED(dsBuf->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID *)&mDSBuf8)))
			{
				ret = true;
			}

			dsBuf->Release();
			dsBuf = 0;
		}
	}

	return ret;
}

void glSound::destroy(void)
{
	IDirectSoundBuffer8 * dsBuf8 = (IDirectSoundBuffer8 *)mDSBuf8;
	if (dsBuf8)
	{
		if (gSoundDevice.isAlready())
		{
			dsBuf8->Release();
		}
	}

	mDSBuf8 = 0;
}

void * glSound::lock(const int offset, const int size)
{
	void * audioPtr = 0;
	DWORD audioSize = 0;
	IDirectSoundBuffer8 * dsBuf8 = (IDirectSoundBuffer8 *)mDSBuf8;

	if (dsBuf8 && offset >= 0 && size > 0)
	{
		dsBuf8->Lock(offset, size, &audioPtr, &audioSize, 0, 0, 0);
	}

	return audioPtr;
}

bool glSound::unlock(void * audioPtr, const int size)
{
	IDirectSoundBuffer8 * dsBuf8 = (IDirectSoundBuffer8 *)mDSBuf8;

	if (dsBuf8 && audioPtr && size > 0)
	{
		if (SUCCEEDED(dsBuf8->Unlock(audioPtr, size, 0, 0)))
		{
			return true;
		}
	}

	return false;
}

bool glSound::play(const bool loop)
{
	IDirectSoundBuffer8 * dsBuf8 = (IDirectSoundBuffer8 *)mDSBuf8;

	if (dsBuf8)
	{
		if (SUCCEEDED(dsBuf8->Play(0, 0, loop ? DSBPLAY_LOOPING : 0)))
		{
			return true;
		}
	}

	return false;
}

bool glSound::stop(void)
{
	IDirectSoundBuffer8 * dsBuf8 = (IDirectSoundBuffer8 *)mDSBuf8;

	if (dsBuf8)
	{
		if (SUCCEEDED(dsBuf8->Stop()))
		{
			return true;
		}
	}

	return false;
}

bool glSound::setVolume(const float volume)
{
	glEngine * engine = glEngine::get();
	LONG ds8Volume = gSoundDevice.engineVolumeToDS8Volume(volume);
	IDirectSoundBuffer8 * dsBuf8 = (IDirectSoundBuffer8 *)mDSBuf8;

	if (dsBuf8)
	{
		if (SUCCEEDED(dsBuf8->SetVolume(ds8Volume)))
		{
			return true;
		}
	}

	return false;
}

bool glSound::getVolume(float & volume)
{
	glEngine * engine = glEngine::get();
	LONG ds8Volume = 0;
	IDirectSoundBuffer8 * dsBuf8 = (IDirectSoundBuffer8 *)mDSBuf8;

	if (dsBuf8)
	{
		if (SUCCEEDED(dsBuf8->GetVolume(&ds8Volume)))
		{
			volume = gSoundDevice.ds8VolumeToEngineVolume(ds8Volume);

			return true;
		}
	}

	return false;
}

bool glSound::isPlaying(bool & playing)
{
	DWORD status = 0;
	IDirectSoundBuffer8 * dsBuf8 = (IDirectSoundBuffer8 *)mDSBuf8;

	if (dsBuf8)
	{
		if (SUCCEEDED(dsBuf8->GetStatus(&status)))
		{
			if (status & DSBSTATUS_PLAYING)
			{
				playing = true;
			}

			return true;
		}
	}

	return false;
}

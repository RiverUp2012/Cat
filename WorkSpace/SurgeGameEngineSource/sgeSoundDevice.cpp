
#include "../SurgeGameEngine.h"
#include "../Include/SurgeGameEnginePrivate.h"

typedef HRESULT (WINAPI * sgeDirectSoundCreate8)(
	LPCGUID pcGuidDevice, 
	LPDIRECTSOUND8 *ppDS8,
	LPUNKNOWN pUnkOuter);
typedef HWND(WINAPI * sgeGetDesktopWindow)(
	VOID);

static sgeDirectSoundCreate8 gDirectSoundCreate8 = 0;
static sgeGetDesktopWindow gGetDesktopWindow = 0;

sgeSoundDevice::sgeSoundDevice()
{
	gDirectSoundCreate8 = (sgeDirectSoundCreate8)
		gModuleDSound.getProcAddressA("DirectSoundCreate8");
	gGetDesktopWindow = (sgeGetDesktopWindow)
		gModuleUser32.getProcAddressA("GetDesktopWindow");

	mDS8 = 0;
	mDSBuf = 0;
}

sgeSoundDevice::~sgeSoundDevice()
{
	destroy();
}

bool sgeSoundDevice::create(sgeWindow & window)
{
	bool ret = false;
	HWND wndHandle = 0;
	DSBUFFERDESC dsBufDesc = { 0 };
	WAVEFORMATEX wavFmt = { 0 };

	if (!mDS8 && !mDSBuf && gDirectSoundCreate8 && gGetDesktopWindow)
	{
		wndHandle = window.isAlready() ? (HWND)window.getHandle() : gGetDesktopWindow();

		if (SUCCEEDED(gDirectSoundCreate8(0, &mDS8, 0)))
		{
			if (SUCCEEDED(mDS8->SetCooperativeLevel(wndHandle, DSSCL_PRIORITY)))
			{
				dsBufDesc.dwSize = sizeof(dsBufDesc);
				dsBufDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER;

				if (SUCCEEDED(mDS8->CreateSoundBuffer(&dsBufDesc, &mDSBuf, 0)))
				{
					wavFmt.wFormatTag = WAVE_FORMAT_PCM;
					wavFmt.nChannels = 2;
					wavFmt.nSamplesPerSec = 44100;
					wavFmt.wBitsPerSample = 16;
					wavFmt.nBlockAlign = wavFmt.nChannels * wavFmt.wBitsPerSample / 8;
					wavFmt.nAvgBytesPerSec = wavFmt.nBlockAlign * wavFmt.nSamplesPerSec;

					if (SUCCEEDED(mDSBuf->SetFormat(&wavFmt)))
					{
						ret = true;
					}
				}
			}
		}
	}

	return true;
}

void sgeSoundDevice::destroy(void)
{
	if (mDSBuf)
	{
		mDSBuf->Release();
		mDSBuf = 0;
	}

	if (mDS8)
	{
		mDS8->Release();
		mDS8 = 0;
	}
}

bool sgeSoundDevice::isAlready(void) const
{
	return mDS8 && mDSBuf ? true : false;
}

IDirectSound8 * sgeSoundDevice::getIDirectSound8(void) const
{
	return mDS8;
}

long sgeSoundDevice::engineVolumeToDS8Volume(const float volume) const
{
	return DSBVOLUME_MIN + (LONG)(volume * (float)(DSBVOLUME_MAX - DSBVOLUME_MIN));
}

float sgeSoundDevice::ds8VolumeToEngineVolume(const long volume) const
{
	return (float)(volume - DSBVOLUME_MIN) / (float)(DSBVOLUME_MAX - DSBVOLUME_MIN);
}
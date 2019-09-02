
#include "../Include/Private.h"
#include "../Include/DS8Common.h"
#include "../Include/CompileConfig.h"

#if defined T_USE_DS8

typedef HRESULT (WINAPI * TDirectSoundCreate8)(
	LPCGUID pcGuidDevice,
	LPDIRECTSOUND8 *ppDS8,
	LPUNKNOWN pUnkOuter);

#define T_MAX_DS8SOUNDDEVIEC (32)

typedef struct _T_DS8SOUNDDEVICE
{
	struct IDirectSound8 * mDS8;
	struct IDirectSoundBuffer * mDSBuf;
}
T_DS8SOUNDDEVICE;

static T_DS8SOUNDDEVICE gDS8SoundDeviceArray[T_MAX_DS8SOUNDDEVIEC] = { 0 };
static T_OBJECT gModuleDSound = 0;
static TDirectSoundCreate8 gDirectSoundCreate8 = 0;

static T_DS8SOUNDDEVICE * TFindUnuseDS8SoundDevice(void)
{
	for (int i = 0; i < T_MAX_DS8SOUNDDEVIEC; ++i)
	{
		if (!gDS8SoundDeviceArray[i].mDS8)
		{
			return &gDS8SoundDeviceArray[i];
		}
	}

	return 0;
}

#endif // T_USE_DS8

T_OBJECT TDS8SoundDeviceCreate(
	T_OBJECT window)
{
#if defined T_USE_DS8

	DSBUFFERDESC dsBufDesc = { 0 };
	WAVEFORMATEX wavFmt = { 0 };

	if (!gModuleDSound)
	{
		gModuleDSound = TModuleLoadW(L"dsound.dll");
		if (gModuleDSound)
		{
			gDirectSoundCreate8 = (TDirectSoundCreate8)TModuleGetProcAddress(
				gModuleDSound,
				L"DirectSoundCreate8");
		}
	}

	HWND wndHandle = TWindowGetHandle(window);
	if (!IsWindow(wndHandle))
	{
		wndHandle = GetDesktopWindow();
	}

	T_DS8SOUNDDEVICE * ds8SoundDeviceImpl = TFindUnuseDS8SoundDevice();
	if (ds8SoundDeviceImpl && gDirectSoundCreate8)
	{
		if (SUCCEEDED(gDirectSoundCreate8(0, &ds8SoundDeviceImpl->mDS8, 0)))
		{
			if (SUCCEEDED(ds8SoundDeviceImpl->mDS8->SetCooperativeLevel(
				wndHandle,
				DSSCL_PRIORITY)))
			{
				dsBufDesc.dwSize = sizeof(dsBufDesc);
				dsBufDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;

				if (SUCCEEDED(ds8SoundDeviceImpl->mDS8->CreateSoundBuffer(
					&dsBufDesc,
					&ds8SoundDeviceImpl->mDSBuf,
					0)))
				{
					wavFmt.wFormatTag = WAVE_FORMAT_PCM;
					wavFmt.nChannels = 2;
					wavFmt.wBitsPerSample = 16;
					wavFmt.nSamplesPerSec = 44100;
					wavFmt.nBlockAlign = wavFmt.nChannels * wavFmt.wBitsPerSample / 8;
					wavFmt.nAvgBytesPerSec = wavFmt.nBlockAlign * wavFmt.nSamplesPerSec;

					if (SUCCEEDED(ds8SoundDeviceImpl->mDSBuf->SetFormat(
						&wavFmt)))
					{
						return (T_OBJECT)ds8SoundDeviceImpl;
					}

					ds8SoundDeviceImpl->mDSBuf->Release();
					ds8SoundDeviceImpl->mDSBuf = 0;
				}
			}

			ds8SoundDeviceImpl->mDS8->Release();
			ds8SoundDeviceImpl->mDS8 = 0;
		}
	}

#endif // T_USE_DS8

	return 0;
}

void TDS8SoundDeviceDestroy(
	T_OBJECT ds8SoundDevice)
{
#if defined T_USE_DS8

	T_DS8SOUNDDEVICE * ds8SoundDeviceImpl = (T_DS8SOUNDDEVICE *)ds8SoundDevice;
	if (ds8SoundDeviceImpl)
	{
		if (ds8SoundDeviceImpl->mDSBuf)
		{
			ds8SoundDeviceImpl->mDSBuf->Release();
			ds8SoundDeviceImpl->mDSBuf = 0;
		}

		if (ds8SoundDeviceImpl->mDS8)
		{
			ds8SoundDeviceImpl->mDS8->Release();
			ds8SoundDeviceImpl->mDS8 = 0;
		}
	}

#endif // T_USE_DS8
}

#if defined T_USE_DS8

struct IDirectSound8 * TDS8SoundDeviceGetIDirectSound8(
	T_OBJECT ds8SoundDevice)
{
	T_DS8SOUNDDEVICE * ds8SoundDeviceImpl = (T_DS8SOUNDDEVICE *)ds8SoundDevice;

	return ds8SoundDeviceImpl ? ds8SoundDeviceImpl->mDS8 : 0;
}

#endif // T_USE_DS8

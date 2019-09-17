
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

typedef HRESULT (WINAPI * glDirectSoundCreate8)(
	LPCGUID pcGuidDevice, 
	LPDIRECTSOUND8 *ppDS8,
	LPUNKNOWN pUnkOuter);
typedef HWND(WINAPI * glGetDesktopWindow)(
	VOID);

static glDirectSoundCreate8 gDirectSoundCreate8 = 0;
static glGetDesktopWindow gGetDesktopWindow = 0;

glSoundDevice::glSoundDevice() {
	gDirectSoundCreate8 = (glDirectSoundCreate8)
		gModuleDSound.getProcAddressA("DirectSoundCreate8");
	gGetDesktopWindow = (glGetDesktopWindow)
		gModuleUser32.getProcAddressA("GetDesktopWindow");
	mDS8 = 0;
	mDSBuf = 0;
}

glSoundDevice::~glSoundDevice() {
	destroy();
}

bool glSoundDevice::create(glWindow & window) {
	bool ret = false;
	HWND wndHandle = 0;
	DSBUFFERDESC dsBufDesc = { 0 };
	WAVEFORMATEX wavFmt = { 0 };
	if (!mDS8 && !mDSBuf && gDirectSoundCreate8 && gGetDesktopWindow) {
		wndHandle = window.isAlready() ? (HWND)window.getHandle() : gGetDesktopWindow();
		if (SUCCEEDED(gDirectSoundCreate8(0, &mDS8, 0))) {
			if (SUCCEEDED(mDS8->SetCooperativeLevel(wndHandle, DSSCL_PRIORITY))) {
				dsBufDesc.dwSize = sizeof(dsBufDesc);
				dsBufDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER;
				if (SUCCEEDED(mDS8->CreateSoundBuffer(&dsBufDesc, &mDSBuf, 0))) {
					wavFmt.wFormatTag = WAVE_FORMAT_PCM;
					wavFmt.nChannels = 2;
					wavFmt.nSamplesPerSec = 44100;
					wavFmt.wBitsPerSample = 16;
					wavFmt.nBlockAlign = wavFmt.nChannels * wavFmt.wBitsPerSample / 8;
					wavFmt.nAvgBytesPerSec = wavFmt.nBlockAlign * wavFmt.nSamplesPerSec;
					if (SUCCEEDED(mDSBuf->SetFormat(&wavFmt))) {
						ret = true;
					}
				}
			}
		}
	}
	return true;
}

void glSoundDevice::destroy(void) {
	if (mDSBuf) {
		mDSBuf->Release();
		mDSBuf = 0;
	}
	if (mDS8) {
		mDS8->Release();
		mDS8 = 0;
	}
}

bool glSoundDevice::isAlready(void) const {
	return mDS8 && mDSBuf ? true : false;
}

IDirectSound8 * glSoundDevice::getIDirectSound8(void) const {
	return mDS8;
}

long glSoundDevice::engineVolumeToDS8Volume(const float volume) const {
	return DSBVOLUME_MIN + (LONG)(volume * (float)(DSBVOLUME_MAX - DSBVOLUME_MIN));
}

float glSoundDevice::ds8VolumeToEngineVolume(const long volume) const {
	return (float)(volume - DSBVOLUME_MIN) / (float)(DSBVOLUME_MAX - DSBVOLUME_MIN);
}

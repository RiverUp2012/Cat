
#include "../GameLibInclude/glSoundDevice.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glGlobalData.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glWindow.h"

typedef HRESULT (WINAPI * glDirectSoundCreate8)(
	LPCGUID pcGuidDevice, 
	LPDIRECTSOUND8 *ppDS8,
	LPUNKNOWN pUnkOuter);
typedef HWND(WINAPI * glGetDesktopWindow)(
	VOID);

namespace {
	static glDirectSoundCreate8 gDirectSoundCreate8 = 0;
	static glGetDesktopWindow gGetDesktopWindow = 0;
}

glSoundDevice::glSoundDevice() {
	if (!gDirectSoundCreate8) {
		gDirectSoundCreate8 = (glDirectSoundCreate8)
			gModuleDSound.getProcAddressA("DirectSoundCreate8");
	}
	if (!gGetDesktopWindow) {
		gGetDesktopWindow = (glGetDesktopWindow)
			gModuleUser32.getProcAddressA("GetDesktopWindow");
	}
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
	HRESULT comRet = S_OK;
	if (!mDS8 && !mDSBuf && gDirectSoundCreate8 && gGetDesktopWindow) {
		wndHandle = window.isAlready() ? (HWND)window.getHandle() : gGetDesktopWindow();
		comRet = gDirectSoundCreate8(0, &mDS8, 0);
		if (SUCCEEDED(comRet)) {
			comRet = mDS8->SetCooperativeLevel(wndHandle, DSSCL_PRIORITY);
			if (SUCCEEDED(comRet)) {
				dsBufDesc.dwSize = sizeof(dsBufDesc);
				dsBufDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER;
				comRet = mDS8->CreateSoundBuffer(&dsBufDesc, &mDSBuf, 0);
				if (SUCCEEDED(comRet)) {
					wavFmt.wFormatTag = WAVE_FORMAT_PCM;
					wavFmt.nChannels = 2;
					wavFmt.nSamplesPerSec = 44100;
					wavFmt.wBitsPerSample = 16;
					wavFmt.nBlockAlign = wavFmt.nChannels * wavFmt.wBitsPerSample / 8;
					wavFmt.nAvgBytesPerSec = wavFmt.nBlockAlign * wavFmt.nSamplesPerSec;
					comRet = mDSBuf->SetFormat(&wavFmt);
					if (SUCCEEDED(comRet)) {
						ret = true;
					}
					else {
						throw glCOMAPIException(L"IDirectSoundBuffer::SetFormat", comRet);
					}
				}
				else {
					throw glCOMAPIException(L"IDirectSound8::CreateSoundBuffer", comRet);
				}
			}
			else {
				throw glCOMAPIException(L"IDirectSound8::SetCooperativeLevel", comRet);
			}
		}
		else {
			throw glCOMAPIException(L"DirectSoundCreate8", comRet);
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

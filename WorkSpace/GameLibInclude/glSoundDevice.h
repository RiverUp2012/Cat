
#pragma once

#include "glNonCopyable.h"

struct IDirectSound8;
struct IDirectSoundBuffer;
class glWindow;

//
// @brief …˘“Ù…Ë±∏¿‡
//
class glSoundDevice : public glNonCopyable {
public:
	glSoundDevice();
	virtual ~glSoundDevice();
public:
	bool create(glWindow & window);
	void destroy(void);
	bool isAlready(void) const;
	IDirectSound8 * getIDirectSound8(void) const;
	long engineVolumeToDS8Volume(const float volume) const;
	float ds8VolumeToEngineVolume(const long volume) const;
private:
	IDirectSound8 * mDS8;
	IDirectSoundBuffer * mDSBuf;
};


#ifndef DS8COMMON_H
#define DS8COMMON_H

#include "CompileConfig.h"
#include "Private.h"

#if defined T_USE_DS8

#	include "../DependLib/DS8/dsound.h"

//---------------------------------------------------------------
// ds8 common
// ds8 公共接口
//---------------------------------------------------------------

//
// 将库音量转换为 ds8 音量
//
extern LONG TDS8LibVolumeToDS8Volume(
	const float libVolume);

//
// 将 ds8 音量转换为库音量
//
extern float TDS8DS8VolumeToLibVolume(
	const LONG ds8Volume);

//---------------------------------------------------------------
// ds8 sound device
// ds8 音频设备相关接口
//---------------------------------------------------------------

//
// 获取 IDirectSound8 接口
//
extern struct IDirectSound8 * TDS8SoundDeviceGetIDirectSound8(
	T_OBJECT ds8SoundDevice);

#endif // T_USE_DS8

#endif // DS8COMMON_H

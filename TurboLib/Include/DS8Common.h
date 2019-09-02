
#ifndef DS8COMMON_H
#define DS8COMMON_H

#include "CompileConfig.h"
#include "Private.h"

#if defined T_USE_DS8

#	include "../DependLib/DS8/dsound.h"

//---------------------------------------------------------------
// ds8 common
// ds8 �����ӿ�
//---------------------------------------------------------------

//
// ��������ת��Ϊ ds8 ����
//
extern LONG TDS8LibVolumeToDS8Volume(
	const float libVolume);

//
// �� ds8 ����ת��Ϊ������
//
extern float TDS8DS8VolumeToLibVolume(
	const LONG ds8Volume);

//---------------------------------------------------------------
// ds8 sound device
// ds8 ��Ƶ�豸��ؽӿ�
//---------------------------------------------------------------

//
// ��ȡ IDirectSound8 �ӿ�
//
extern struct IDirectSound8 * TDS8SoundDeviceGetIDirectSound8(
	T_OBJECT ds8SoundDevice);

#endif // T_USE_DS8

#endif // DS8COMMON_H

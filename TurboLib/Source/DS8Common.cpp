
#include "../Include/Private.h"
#include "../Include/DS8Common.h"
#include "../Include/CompileConfig.h"

#if defined T_USE_DS8

LONG TDS8LibVolumeToDS8Volume(
	const float libVolume)
{
	return DSBVOLUME_MIN + (LONG)(libVolume * (float)(DSBVOLUME_MAX - DSBVOLUME_MIN));
}

float TDS8DS8VolumeToLibVolume(
	const LONG ds8Volume)
{
	return (float)(ds8Volume - DSBVOLUME_MIN) / (float)(DSBVOLUME_MAX - DSBVOLUME_MIN);
}

#endif // T_USE_DS8

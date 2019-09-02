
#include "../TurboLib.h"
#include "../Include/Private.h"

int TAbsInt(
	const int value)
{
	return value < 0 ? -1 * value : value;
}

float TAbsFloat(
	const float value)
{
	return value < 0 ? -1.0f * value : value;
}

double TAbsDouble(
	const double value)
{
	return value < 0 ? -1.0 * value : value;
}

void TRandInit(void)
{
	srand(GetTickCount());
}

float TRandFloat(
	const float min,
	const float max)
{
	return min + ((float)rand() / (float)RAND_MAX) * (max - min);
}

int TRandInt(
	const int min,
	const int max)
{
	return min + (rand() % (max - min));
}


#include "../TurboLib.h"

unsigned int TColorGetARGB(
	const unsigned char alpha,
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

unsigned int TColorGetRGB(
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue)
{
	return (0xff << 24) | (red << 16) | (green << 8) | blue;
}

unsigned char TColorGetAlpha(
	const unsigned int argb)
{
	return (unsigned char)((argb & 0xff000000) >> 24);
}

unsigned char TColorGetRed(
	const unsigned int argb)
{
	return (unsigned char)((argb & 0x00ff0000) >> 16);
}

unsigned char TColorGetGreen(
	const unsigned int argb)
{
	return (unsigned char)((argb & 0x0000ff00) >> 8);
}

unsigned char TColorGetBlue(
	const unsigned int argb)
{
	return (unsigned char)(argb & 0x0000ff);
}

unsigned int TColorSetAlpha(
	unsigned int * argb,
	const unsigned char alpha)
{
	if (argb)
	{
		*argb = (*argb & 0x00ffffff) | (alpha << 24);
		return *argb;
	}

	return 0;
}

unsigned int TColorSetRed(
	unsigned int * argb,
	const unsigned char red)
{
	if (argb)
	{
		*argb = (*argb & 0xff00ffff) | (red << 16);
		return *argb;
	}

	return 0;
}

unsigned int TColorSetGreen(
	unsigned int * argb,
	const unsigned char green)
{
	if (argb)
	{
		*argb = (*argb & 0xffff00ff) | (green << 8);
		return *argb;
	}

	return 0;
}

unsigned int TColorSetBlue(
	unsigned int * argb,
	const unsigned char blue)
{
	if (argb)
	{
		*argb = (*argb & 0xffffff00) | blue;
		return *argb;
	}

	return 0;
}

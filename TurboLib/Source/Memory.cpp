
#include "../TurboLib.h"

void * TMalloc(
	const int bytesToMalloc)
{
	return bytesToMalloc > 0 ? malloc(bytesToMalloc) : 0;
}

void * TMalloc0(
	const int bytesToMalloc)
{
	void * buffer = 0;
	unsigned char * bufferTemp = 0;

	if (bytesToMalloc > 0)
	{
		buffer = malloc(bytesToMalloc);
		if (buffer)
		{
			bufferTemp = (unsigned char *)buffer;

			for (int i = 0; i < bytesToMalloc; ++i)
			{
				bufferTemp[i] = 0;
			}
		}
	}

	return buffer;
}

void TFree(
	void * bufferToFree)
{
	if (bufferToFree)
	{
		free(bufferToFree);
		bufferToFree = 0;
	}
}

void * TRealloc(
	void * bufferToRealloc,
	const int bytesToRealloc)
{
	return bytesToRealloc >= 0 ? realloc(bufferToRealloc, bytesToRealloc) : 0;
}

void * TMemset(
	void * buffer,
	const int bytesToSet,
	const unsigned char valueToSet)
{
	unsigned char * bufferTemp = (unsigned char *)buffer;

	if (bufferTemp)
	{
		for (int i = 0; i < bytesToSet; ++i)
		{
			bufferTemp[i] = valueToSet;
		}
	}

	return buffer;
}

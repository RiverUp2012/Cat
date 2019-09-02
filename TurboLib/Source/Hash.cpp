
#include "../TurboLib.h"

int THashStringW(
	const wchar_t * string)
{
	int hash = 0;

	if (string)
	{
		while (*string)
		{
			hash = hash * 101 + *string;
			++string;
		}
	}

	return TAbsInt(hash);
}

int THashStringA(
	const char * string)
{
	int hash = 0;

	if (string)
	{
		while (*string)
		{
			hash = hash * 101 + *string;
			++string;
		}
	}

	return TAbsInt(hash);
}

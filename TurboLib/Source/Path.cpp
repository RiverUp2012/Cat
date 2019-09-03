
#include "../TurboLib.h"

int TPathExtractFileNameWithExtW(
	const wchar_t * path,
	wchar_t * fileNameWithExt,
	const int fileNameWithExtSize)
{
	int pathLength = 0;

	if (path && fileNameWithExt && fileNameWithExtSize > 0)
	{
		pathLength = TStringLengthW(path);
		for (int i = pathLength - 1; i >= 0; --i)
		{
			if (L'\\' == path[i] || L'/' == path[i])
			{
				TStringCopyW(
					fileNameWithExt,
					&path[i + 1],
					pathLength - i - 1);
				fileNameWithExt[pathLength - i - 1] = L'\0';

				return T_TRUE;
			}
		}
	}

	return T_FALSE;
}

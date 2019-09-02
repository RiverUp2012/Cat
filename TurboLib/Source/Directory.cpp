
#include "../TurboLib.h"
#include "../Include/Private.h"

int TDirectoryGetAppW(
	wchar_t * appDir,
	const int appDirSize)
{
	int appDirLength = 0;

	if (appDir && appDirSize > 0)
	{
		if (GetModuleFileNameW(0, appDir, appDirSize))
		{
			appDirLength = TStringLengthW(appDir);

			for (int i = appDirLength - 1; i >= 0; --i)
			{
				if (L'\\' == appDir[i] || L'/' == appDir[i])
				{
					appDir[i + 1] = L'\0';
					break;
				}
			}

			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TDirectoryGetAppA(
	char * appDir,
	const int appDirSize)
{
	int appDirLength = 0;

	if (appDir && appDirSize > 0)
	{
		if (GetModuleFileNameA(0, appDir, appDirSize))
		{
			appDirLength = TStringLengthA(appDir);

			for (int i = appDirLength - 1; i >= 0; --i)
			{
				if ('\\' == appDir[i] || '/' == appDir[i])
				{
					appDir[i + 1] = '\0';
					break;
				}
			}

			return T_TRUE;
		}
	}

	return T_FALSE;
}

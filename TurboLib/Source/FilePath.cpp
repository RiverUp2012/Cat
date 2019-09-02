
#include "../TurboLib.h"

wchar_t * TFilePathAppendSlashW(
	wchar_t * path)
{
	int pathLength = 0;

	if (path)
	{
		pathLength = TStringLengthW(path);
		if (pathLength > 0)
		{
			if (L'\\' != path[pathLength - 1] && L'/' != path[pathLength - 1])
			{
				path[pathLength] = L'\\';
				path[pathLength + 1] = L'\0';
			}
		}
	}

	return path;
}

char * TFilePathAppendSlashA(
	char * path)
{
	int pathLength = 0;

	if (path)
	{
		pathLength = TStringLengthA(path);
		if (pathLength > 0)
		{
			if ('\\' != path[pathLength - 1] && '/' != path[pathLength - 1])
			{
				path[pathLength] = '\\';
				path[pathLength + 1] = '\0';
			}
		}
	}

	return path;
}

wchar_t * TFilePathAppendW(
	wchar_t * path,
	const wchar_t * append)
{
	int pathLength = 0;
	int appendLength = append ? TStringLengthW(append) : 0;

	if (path && append && appendLength > 0)
	{
		TFilePathAppendSlashW(path);
		pathLength = TStringLengthW(path);
		TStringCopyW(&(path[pathLength]), append, appendLength);
	}

	return path;
}

char * TFilePathAppendA(
	char * path,
	const char * append)
{
	int pathLength = 0;
	int appendLength = append ? TStringLengthA(append) : 0;

	if (path && append && appendLength > 0)
	{
		TFilePathAppendSlashA(path);
		pathLength = TStringLengthA(path);
		TStringCopyA(&(path[pathLength]), append, appendLength);
	}

	return path;
}

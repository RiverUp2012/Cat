
#include "../TurboLib.h"
#include "../Include/Private.h"

#define T_MAX_INIFILE (32)
#define T_MAX_INIFILE_FILE_NAME_SIZE (520)

typedef struct _T_INIFILE
{
	wchar_t mFileName[T_MAX_INIFILE_FILE_NAME_SIZE];
	int mInUse;
}
T_INIFILE;

static T_INIFILE gIniFileArray[T_MAX_INIFILE] = { 0 };

static T_INIFILE * TFindUnuseIniFile(void)
{
	for (int i = 0; i < T_MAX_INIFILE; ++i)
	{
		if (!gIniFileArray[i].mInUse)
		{
			return &gIniFileArray[i];
		}
	}

	return 0;
}

T_OBJECT TIniFileCreateW(
	const wchar_t * iniFileName)
{
	if (iniFileName)
	{
		T_INIFILE * iniFileImpl = TFindUnuseIniFile();
		if (iniFileImpl)
		{
			iniFileImpl->mInUse = T_TRUE;
			TStringCopyW(iniFileImpl->mFileName, iniFileName, 0);

			return (T_OBJECT)iniFileImpl;
		}
	}

	return 0;
}

void TIniFileDestroy(
	T_OBJECT iniFile)
{
	T_INIFILE * iniFileImpl = (T_INIFILE *)iniFile;
	if (iniFileImpl)
	{
		TMemset(iniFileImpl, sizeof(T_INIFILE), 0);
	}
}

int TIniFileReadStringW(
	T_OBJECT iniFile,
	const wchar_t * sectionName,
	const wchar_t * keyName,
	wchar_t * value,
	const int valueSize)
{
	T_INIFILE * iniFileImpl = (T_INIFILE *)iniFile;
	if (iniFileImpl && sectionName && keyName && value && valueSize)
	{
		if (GetPrivateProfileStringW(
			sectionName,
			keyName,
			0,
			value,
			valueSize,
			iniFileImpl->mFileName))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TIniFileReadIntW(
	T_OBJECT iniFile,
	const wchar_t * sectionName,
	const wchar_t * keyName,
	int * value)
{
	wchar_t valueTemp[64] = { 0 };

	if (value && TIniFileReadStringW(iniFile, sectionName, keyName, valueTemp, 64))
	{
		*value = _wtoi(valueTemp);

		return T_TRUE;
	}

	return T_FALSE;
}

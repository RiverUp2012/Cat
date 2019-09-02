
#include "../TurboLib.h"
#include "../Include/Private.h"

static int gParamCount = 0;
static wchar_t ** gParamArray = 0;
static int gInitFlag = T_FALSE;

static void TCmdLineInit(void)
{
	wchar_t * cmdLine = 0;
	wchar_t ** paramArray = 0;

	if (!gInitFlag)
	{
		cmdLine = GetCommandLineW();
		if (cmdLine)
		{
			paramArray = CommandLineToArgvW(cmdLine, &gParamCount);
			if (paramArray)
			{
				gParamArray = (wchar_t **)TMalloc(sizeof(wchar_t *)* gParamCount);
				if (gParamArray)
				{
					for (int i = 0; i < gParamCount; ++i)
					{
						gParamArray[i] = TStringDuplicateW(paramArray[i]);
					}
				}
			}
		}

		gInitFlag = T_TRUE;
	}
}

int TCmdLineReadParam(
	const int paramIndex,
	wchar_t * param,
	const int paramSize)
{
	TCmdLineInit();

	if (paramIndex >= 0 &&
		paramIndex < gParamCount &&
		gParamArray &&
		gParamArray[paramIndex] &&
		param &&
		paramSize > 0)
	{
		TStringCopyW(param, gParamArray[paramIndex], 0);

		return T_TRUE;
	}

	return T_FALSE;
}

int TCmdLineIsParamPresented(
	const wchar_t * param,
	int * paramIndex)
{
	TCmdLineInit();

	if (param && gParamArray)
	{
		for (int i = 0; i < gParamCount; ++i)
		{
			if (gParamArray[i] && 0 == wcscmp(gParamArray[i], param))
			{
				if (paramIndex)
				{
					*paramIndex = i;
				}

				return T_TRUE;
			}
		}
	}

	return T_FALSE;
}

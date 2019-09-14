
#include "../SurgeGameEngine.h"
#include "../Include/SurgeGameEnginePrivate.h"

bool sgeStringTool::a2w(const char * stringA, sgeStringW & stringW)
{
	int stringALength = stringA ? sgeStringA::getLength(stringA) : 0;
	int stringWLength = 0;

	if (stringALength > 0)
	{
		stringWLength = MultiByteToWideChar(
			CP_ACP,
			0,
			stringA,
			stringALength,
			0,
			0);
		if (stringWLength > 0 && stringW.resize(stringWLength + 1))
		{
			MultiByteToWideChar(
				CP_ACP,
				0,
				stringA,
				stringALength,
				stringW.getBuffer(),
				stringW.getCapacity());
			stringW.setAt(stringWLength, stringW.getNullChar());

			return true;
		}
	}

	return false;
}

bool sgeStringTool::w2a(const wchar_t * stringW, sgeStringA & stringA)
{
	int stringALength = 0;
	int stringWLength = stringW ? sgeStringW::getLength(stringW) : 0;

	if (stringWLength > 0)
	{
		stringALength = WideCharToMultiByte(
			CP_ACP,
			0,
			stringW,
			stringWLength,
			0,
			0,
			0,
			0);
		if (stringALength > 0 && stringA.resize(stringALength + 1))
		{
			WideCharToMultiByte(
				CP_ACP,
				0,
				stringW,
				stringWLength,
				stringA.getBuffer(),
				stringA.getCapacity(),
				0,
				0);
			stringA.setAt(stringALength, stringA.getNullChar());

			return true;
		}
	}

	return false;
}

int sgeStringTool::findA(const char * string, const char * subString)
{
	if (string && subString)
	{
		const char * findRet = strstr(string, subString);
		if (findRet)
		{
			return (int)string - (int)findRet;
		}
	}

	return -1;
}

int sgeStringTool::findW(const wchar_t * string, const wchar_t * subString)
{
	if (string && subString)
	{
		const wchar_t * findRet = wcsstr(string, subString);
		if (findRet)
		{
			return (int)string - (int)findRet;
		}
	}

	return -1;
}

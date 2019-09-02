
#include "../TurboLib.h"
#include "../Include/Private.h"

wchar_t * TStringAllocW(
	const int capacity)
{
	wchar_t * string = 0;

	if (capacity > 0)
	{
		string = (wchar_t *)TMalloc(sizeof(wchar_t)* capacity);
		if (string)
		{
			string[0] = L'\0';
		}
	}

	return string;
}

char * TStringAllocA(
	const int capacity)
{
	char * string = 0;

	if (capacity > 0)
	{
		string = (char *)TMalloc(sizeof(char)* capacity);
		if (string)
		{
			string[0] = '\0';
		}
	}

	return string;
}

int TStringLengthW(
	const wchar_t * string)
{
	int stringLength = 0;

	if (string)
	{
		while (*string)
		{
			++stringLength;
			++string;
		}
	}

	return stringLength;
}

int TStringLengthA(
	const char * string)
{
	int stringLength = 0;

	if (string)
	{
		while (*string)
		{
			++stringLength;
			++string;
		}
	}

	return stringLength;
}

wchar_t * TStringCopyW(
	wchar_t * destString,
	const wchar_t * sourceString,
	const int copyChars)
{
	int stringLength = 0;

	if (destString && sourceString)
	{
		if (copyChars <= 0)
		{
			stringLength = TStringLengthW(sourceString);

			for (int i = 0; i < stringLength; ++i)
			{
				destString[i] = sourceString[i];
			}

			destString[stringLength] = L'\0';
		}
		else
		{
			for (int i = 0; i < copyChars; ++i)
			{
				destString[i] = sourceString[i];
			}

			destString[copyChars] = L'\0';
		}
	}

	return destString;
}

char * TStringCopyA(
	char * destString,
	const char * sourceString,
	const int copyChars)
{
	int stringLength = 0;

	if (destString && sourceString)
	{
		if (copyChars <= 0)
		{
			stringLength = TStringLengthA(sourceString);

			for (int i = 0; i < stringLength; ++i)
			{
				destString[i] = sourceString[i];
			}

			destString[stringLength] = '\0';
		}
		else
		{
			for (int i = 0; i < copyChars; ++i)
			{
				destString[i] = sourceString[i];
			}

			destString[copyChars] = '\0';
		}
	}

	return destString;
}

wchar_t * TStringDuplicateW(
	const wchar_t * string)
{
	wchar_t * copyString = 0;
	int stringLength = 0;

	if (string)
	{
		stringLength = TStringLengthW(string);
		if (stringLength > 0)
		{
			copyString = (wchar_t *)TMalloc(sizeof(wchar_t) * (stringLength + 1));
			if (copyString)
			{
				TStringCopyW(copyString, string, stringLength);
				copyString[stringLength] = L'\0';
			}
		}
	}

	return copyString;
}

char * TStringDuplicateA(
	const char * string)
{
	char * copyString = 0;
	int stringLength = 0;

	if (string)
	{
		stringLength = TStringLengthA(string);
		if (stringLength > 0)
		{
			copyString = (char *)TMalloc(sizeof(char)* (stringLength + 1));
			if (copyString)
			{
				TStringCopyA(copyString, string, stringLength);
				copyString[stringLength] = '\0';
			}
		}
	}

	return copyString;
}

int TStringIsEqualW(
	const wchar_t * destString,
	const wchar_t * sourceString)
{
	int destStringLength = 0;
	int sourceStringLength = 0;

	if (destString && sourceString)
	{
		destStringLength = TStringLengthW(destString);
		sourceStringLength = TStringLengthW(sourceString);

		if (destStringLength > 0 && destStringLength == sourceStringLength)
		{
			for (int i = 0; i < destStringLength; ++i)
			{
				if (destString[i] != sourceString[i])
				{
					return T_FALSE;
				}
			}

			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TStringIsEqualA(
	const char * destString,
	const char * sourceString)
{
	int destStringLength = 0;
	int sourceStringLength = 0;

	if (destString && sourceString)
	{
		destStringLength = TStringLengthA(destString);
		sourceStringLength = TStringLengthA(sourceString);

		if (destStringLength > 0 && destStringLength == sourceStringLength)
		{
			for (int i = 0; i < destStringLength; ++i)
			{
				if (destString[i] != sourceString[i])
				{
					return T_FALSE;
				}
			}

			return T_TRUE;
		}
	}

	return T_FALSE;
}

char * TStringW2A(
	const wchar_t * stringW)
{
	char * stringA = 0;
	int stringALength = 0;
	int stringWLength = 0;

	if (stringW)
	{
		stringWLength = TStringLengthW(stringW);
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
			if (stringALength > 0)
			{
				stringA = (char *)TMalloc(sizeof(char)* (stringALength + 1));
				if (stringA)
				{
					WideCharToMultiByte(
						CP_ACP,
						0,
						stringW,
						stringWLength,
						stringA,
						stringALength + 1,
						0,
						0);
					stringA[stringALength] = '\0';
				}
			}
		}
	}

	return stringA;
}

wchar_t * TStringA2W(
	const char * stringA)
{
	wchar_t * stringW = 0;
	int stringWLength = 0;
	int stringALength = 0;

	if (stringA)
	{
		stringALength = TStringLengthA(stringA);
		if (stringALength > 0)
		{
			stringWLength = MultiByteToWideChar(
				CP_ACP,
				0,
				stringA,
				stringALength,
				0,
				0);
			if (stringWLength > 0)
			{
				stringW = (wchar_t *)TMalloc(sizeof(wchar_t)* (stringWLength + 1));
				if (stringW)
				{
					MultiByteToWideChar(
						CP_ACP,
						0,
						stringA,
						stringALength,
						stringW,
						stringWLength);
					stringW[stringWLength] = L'\0';
				}
			}
		}
	}

	return stringW;
}

wchar_t * TStringFormatW(
	const wchar_t * format,
	...)
{
	va_list vl = { 0 };

	va_start(vl, format);

	return TStringFormatVW(format, vl);
}

char * TStringFormatA(
	const char * format,
	...)
{
	va_list vl = { 0 };

	va_start(vl, format);

	return TStringFormatVA(format, vl);
}

wchar_t * TStringFormatVW(
	const wchar_t * format,
	const va_list vl)
{
	wchar_t * string = 0;
	int stringLength = 0;

	if (format && vl)
	{
		stringLength = _vscwprintf(format, vl);
		if (stringLength > 0)
		{
			string = TStringAllocW(stringLength + 1);
			if (string)
			{
				vswprintf_s(string, stringLength + 1, format, vl);
				string[stringLength] = L'\0';
			}
		}
	}

	return string;
}

char * TStringFormatVA(
	const char * format,
	const va_list vl)
{
	char * string = 0;
	int stringLength = 0;

	if (format && vl)
	{
		stringLength = _vcprintf(format, vl);
		if (stringLength > 0)
		{
			string = TStringAllocA(stringLength + 1);
			if (string)
			{
				vsprintf_s(string, stringLength + 1, format, vl);
				string[stringLength] = '\0';
			}
		}
	}

	return string;
}

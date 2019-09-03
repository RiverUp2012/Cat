
#include "../TurboLib.h"
#include "../Include/Private.h"

#define T_MAX_LOG_FILE_NAME_SIZE (520)

typedef struct _T_LOG
{
	T_OBJECT mMutex;
	T_OBJECT mLogFile;
	wchar_t mLogFileName[T_MAX_LOG_FILE_NAME_SIZE];
	int mToDebugView;
}
T_LOG;

static T_LOG gLog = { 0 };

int TLogStartupW(
	const wchar_t * logFileName,
	const int toDebugView)
{
	int ret = T_FALSE;

	if (!gLog.mLogFile && !gLog.mMutex && logFileName)
	{
		gLog.mMutex = TMutexCreate();
		if (gLog.mMutex)
		{
			TMutexLock(gLog.mMutex);
			{
				gLog.mLogFile = TFileOpenW(logFileName, T_FALSE, T_TRUE);
				if (gLog.mLogFile)
				{
					TStringCopyW(gLog.mLogFileName, logFileName, 0);
					gLog.mToDebugView = toDebugView;

					ret = T_TRUE;
				}
			}
			TMutexUnlock(gLog.mMutex);
		}
	}

	return ret;
}

int TLogStartupA(
	const char * logFileName,
	const int toDebugView)
{
	int ret = T_FALSE;
	wchar_t * logFileNameW = 0;

	if (logFileName)
	{
		logFileNameW = TStringA2W(logFileName);
		if (logFileNameW)
		{
			ret = TLogStartupW(logFileNameW, toDebugView);

			TFree(logFileNameW);
			logFileNameW = 0;
		}
	}

	return ret;
}

void TLogShutdown(void)
{
	TMutexLock(gLog.mMutex);
	{
		if (gLog.mLogFile)
		{
			TFileClose(gLog.mLogFile);
			gLog.mLogFile = 0;
		}
	}
	TMutexUnlock(gLog.mMutex);

	if (gLog.mMutex)
	{
		TMutexDestroy(gLog.mMutex);
		gLog.mMutex = 0;
	}

	TMemset(gLog.mLogFileName, sizeof(gLog.mLogFileName), 0);
}

int TLogWriteFormatMessageW(
	const wchar_t * format,
	...)
{
	int ret = T_FALSE;
	va_list vl = { 0 };
	wchar_t * messageW = 0;
	char * messageA = 0;

	if (gLog.mLogFile && gLog.mMutex && format)
	{
		TMutexLock(gLog.mMutex);
		{
			va_start(vl, format);
			{
				messageW = TStringFormatVW(format, vl);
				if (messageW)
				{
					messageA = TStringW2A(messageW);
					if (messageA)
					{
						if (TFileWrite(gLog.mLogFile, messageA, sizeof(char)* TStringLengthA(messageA)))
						{
							if (gLog.mToDebugView)
							{
								OutputDebugStringA(messageA);
							}

							ret = T_TRUE;
						}

						TFree(messageA);
						messageA = 0;
					}

					TFree(messageW);
					messageW = 0;
				}
			}
			va_end(vl);
		}
		TMutexUnlock(gLog.mMutex);
	}

	return ret;
}

int TLogWriteFormatMessageA(
	const char * format,
	...)
{
	int ret = T_FALSE;
	va_list vl = { 0 };
	char * message = 0;

	if (gLog.mLogFile && gLog.mMutex && format)
	{
		TMutexLock(gLog.mMutex);
		{
			va_start(vl, format);
			{
				message = TStringFormatVA(format, vl);
				if (message)
				{
					if (TFileWrite(gLog.mLogFile, message, sizeof(char)* TStringLengthA(message)))
					{
						if (gLog.mToDebugView)
						{
							OutputDebugStringA(message);
						}

						ret = T_TRUE;
					}

					TFree(message);
					message = 0;
				}
			}
			va_end(vl);
		}
		TMutexUnlock(gLog.mMutex);
	}

	return ret;
}

int TLogWriteMesageW(
	const wchar_t * message)
{
	int ret = T_FALSE;
	char * messageA = 0;

	if (gLog.mLogFile && gLog.mMutex && message)
	{
		TMutexLock(gLog.mMutex);
		{
			messageA = TStringW2A(message);
			if (messageA)
			{
				if (TFileWrite(gLog.mLogFile, messageA, sizeof(char)* TStringLengthA(messageA)))
				{
					if (gLog.mToDebugView)
					{
						OutputDebugStringA(messageA);
					}

					ret = T_TRUE;
				}

				TFree(messageA);
				messageA = 0;
			}
		}
		TMutexUnlock(gLog.mMutex);
	}

	return ret;
}

int TLogWriteMesageA(
	const char * message)
{
	int ret = T_FALSE;

	if (gLog.mLogFile && gLog.mMutex && message)
	{
		TMutexLock(gLog.mMutex);
		{
			if (TFileWrite(gLog.mLogFile, message, sizeof(char)* TStringLengthA(message)))
			{
				if (gLog.mToDebugView)
				{
					OutputDebugStringA(message);
				}

				ret = T_TRUE;
			}
		}
		TMutexUnlock(gLog.mMutex);
	}

	return ret;
}

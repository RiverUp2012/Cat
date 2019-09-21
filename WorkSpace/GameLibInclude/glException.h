
#pragma once

//
// @brief 异常类
//
class glException {
public:
	glException();
	glException(const wchar_t * message);
	virtual ~glException();
public:
	const wchar_t * getMessage(void) const;
protected:
	wchar_t mMessage[520];
};

//
// @brief Win32 API 异常类
//
class glWin32APIException : public glException {
public:
	glWin32APIException();
	glWin32APIException(const wchar_t * win32APIName, const unsigned int win32LastError);
	virtual ~glWin32APIException();
protected:
	unsigned int mWin32LastError;
};

//
// @brief COM API 异常类
//
class glCOMAPIException : public glException {
public:
	glCOMAPIException();
	glCOMAPIException(const wchar_t * comAPIName, const long comRet);
	virtual ~glCOMAPIException();
protected:
	long mComRet;
};

//
// @brief SOCKET API 异常类
//
class glSocketAPIException : public glException {
public:
	glSocketAPIException();
#if defined WIN64 || defined _WIN64
	glSocketAPIException(
		const wchar_t * socketAPIName,
		const __int64 socket,
		const int wsaLastError);
#else
	glSocketAPIException(
		const wchar_t * socketAPIName,
		const int socket,
		const int wsaLastError);
#endif
	virtual ~glSocketAPIException();
protected:
#if defined WIN64 || defined _WIN64
	__int64 mSocket;
#else
	int mSocket;
#endif
	int mWSALastError;
};

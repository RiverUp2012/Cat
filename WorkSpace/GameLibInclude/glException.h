
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
public:
	unsigned int getWin32LastError(void) const;
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
public:
	long getComRet(void) const;
protected:
	long mComRet;
};

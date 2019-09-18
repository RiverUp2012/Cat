
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

glException::glException() {
	mMessage[0] = L'\0';
}

glException::glException(const wchar_t * message) {
	const int messageDim = GL_DIM(mMessage);
	const int messageLength = message ? glStringW::getLength(message) : 0;
	if (message && messageLength > 0) {
		if (messageLength >= messageDim) {
			glStringW::copy(mMessage, message, messageDim - 1);
			mMessage[messageDim - 1] = L'\0';
		}
	}
	else {
		mMessage[0] = L'\0';
	}
}

glException::~glException() {

}

const wchar_t * glException::getMessage(void) const {
	return mMessage;
}

glWin32APIException::glWin32APIException() {

}

glWin32APIException::glWin32APIException(const wchar_t * win32APIName, const unsigned int win32LastError) {
	swprintf_s(
		mMessage,
		L"Call Win32 API %s() Failed, GetLastError() : %d",
		(win32APIName ? win32APIName : L""),
		win32LastError);
	mWin32LastError = win32LastError;
}

glWin32APIException::~glWin32APIException() {

}

unsigned int glWin32APIException::getWin32LastError(void) const {
	return mWin32LastError;
}

glCOMAPIException::glCOMAPIException() {
	mComRet = 0;
}

glCOMAPIException::glCOMAPIException(const wchar_t * comAPIName, const long comRet) {
	swprintf_s(
		mMessage,
		L"Call COM API %s() Failed, HRESULT : 0x%X",
		(comAPIName ? comAPIName : L""),
		comRet);
	mComRet = comRet;
}

glCOMAPIException::~glCOMAPIException() {

}

long glCOMAPIException::getComRet(void) const {
	return mComRet;
}

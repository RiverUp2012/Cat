
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

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
	mWin32LastError = 0;
}

glException::glException(const wchar_t * win32APIName, const unsigned int win32LastError) {
	swprintf_s(
		mMessage,
		L"Call Win32 API %s() Failed, GetLastError() : %d",
		(win32APIName ? win32APIName : L""),
		win32LastError);
	mWin32LastError = win32LastError;
}

glException::~glException() {

}

const wchar_t * glException::getMessage(void) const {
	return mMessage;
}

unsigned int glException::getWin32LastError(void) const {
	return mWin32LastError;
}

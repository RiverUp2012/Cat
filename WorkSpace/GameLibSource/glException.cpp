
#include "../GameLib.h"

glException::glException(const wchar_t * message) {
	mMessage = message;
	mWin32LastError = 0;
}

glException::glException(const unsigned int win32LastError) {
	mMessage = L"";
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

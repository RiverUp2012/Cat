
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glString.h"
#include "../GameLibInclude/glDefine.h"
#include "../GameLibInclude/glPrivate.h"

glException::glException() {
	mMessage[0] = glStringW::getNullChar();
}

glException::glException(const wchar_t * message) {
	const int messageDim = GL_DIM(mMessage);
	const int messageLength = message ? glStringW::getLength(message) : 0;
	if (message && messageLength > 0) {
		if (messageLength >= messageDim) {
			glStringW::copy(mMessage, message, messageDim - 1);
			mMessage[messageDim - 1] = glStringW::getNullChar();
		}
	}
	else {
		mMessage[0] = glStringW::getNullChar();
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

glSocketAPIException::glSocketAPIException() {

}

#if defined WIN64 || defined _WIN64
glSocketAPIException::glSocketAPIException(
	const wchar_t * socketAPIName,
	const __int64 socket,
	const int wsaLastError) {
	swprintf_s(
		mMessage,
		L"Call Socket API %s() Failed, SOCKET : %lld, WSAGetLastError() : %d",
		(socketAPIName ? socketAPIName : L""),
		socket,
		wsaLastError);
	mSocket = socket;
	mWSALastError = wsaLastError;
}
#else
glSocketAPIException::glSocketAPIException(
	const wchar_t * socketAPIName,
	const int socket,
	const int wsaLastError) {
	swprintf_s(
		mMessage,
		L"Call Socket API %s() Failed, SOCKET : %d, WSAGetLastError() : %d",
		(socketAPIName ? socketAPIName : L""),
		socket,
		wsaLastError);
	mSocket = socket;
	mWSALastError = wsaLastError;
}
#endif

glSocketAPIException::~glSocketAPIException() {

}

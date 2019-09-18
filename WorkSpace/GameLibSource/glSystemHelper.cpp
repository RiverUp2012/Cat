
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

bool glSystemHelper::getCurrentUserNameW(glStringW & userName) {
	wchar_t userNameTemp[520] = { 0 };
	DWORD userNameTempSize = GL_DIM(userNameTemp);
	if (GetUserNameW(userNameTemp, &userNameTempSize)) {
		userName = userNameTemp;
		return true;
	}
	else {
		throw glWin32APIException(L"GetUserNameW", GetLastError());
	}
	return false;
}

bool glSystemHelper::getSystemDirectoryW(glStringW & systemDir) {
	wchar_t systemDirTemp[520] = { 0 };
	if (GetSystemDirectoryW(systemDirTemp, GL_DIM(systemDirTemp))) {
		systemDir = systemDirTemp;
		return true;
	}
	else {
		throw glWin32APIException(L"GetSystemDirectoryW", GetLastError());
	}
	return false;
}

bool glSystemHelper::getWindowDirectoryW(glStringW & windowDir) {
	wchar_t windowDirTemp[520] = { 0 };
	if (GetWindowsDirectoryW(windowDirTemp, GL_DIM(windowDirTemp))) {
		windowDir = windowDirTemp;
		return true;
	}
	else {
		throw glWin32APIException(L"GetWindowsDirectoryW", GetLastError());
	}
	return false;
}

bool glSystemHelper::getComputerNameW(glStringW & computerName) {
	wchar_t computerNameTemp[520] = { 0 };
	DWORD computerNameTempSize = GL_DIM(computerNameTemp);
	if (GetComputerNameW(computerNameTemp, &computerNameTempSize)) {
		computerName = computerNameTemp;
		return true;
	}
	else {
		throw glWin32APIException(L"GetComputerNameW", GetLastError());
	}
	return false;
}

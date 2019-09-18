
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

bool glModuleResourceHelper::getResourceW(
	const int resourceID,
	const wchar_t * resourceType,
	glResourceInfo & resourceInfo) {
	HMODULE moduleHandle = 0;
	HRSRC hRSRC = 0;
	HGLOBAL hGlobal = 0;
	if (resourceType) {
		moduleHandle = GetModuleHandleW(0);
		if (moduleHandle) {
			hRSRC = FindResourceW(moduleHandle, MAKEINTRESOURCEW(resourceID), resourceType);
			if (hRSRC) {
				hGlobal = LoadResource(moduleHandle, hRSRC);
				if (hGlobal) {
					resourceInfo.mSize = SizeofResource(moduleHandle, hRSRC);
					resourceInfo.mData = LockResource(hGlobal);
					return true;
				}
				else {
					throw glWin32APIException(L"LoadResource", GetLastError());
				}
			}
			else {
				throw glWin32APIException(L"FindResourceW", GetLastError());
			}
		}
		else {
			throw glWin32APIException(L"GetModuleHandleW", GetLastError());
		}
	}
	return false;
}

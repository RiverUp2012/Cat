
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

bool glDesktopHelper::getDesktopSize(glSize<int> & size) {
	size.mWidth = GetSystemMetrics(SM_CXSCREEN);
	size.mHeight = GetSystemMetrics(SM_CYSCREEN);
	return false;
}

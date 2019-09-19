
#include "../GameLibInclude/glDesktopHelper.h"
#include "../GameLibInclude/glPrivate.h"

bool glDesktopHelper::getDesktopSize(glSize<int> & size) {
	size.mWidth = GetSystemMetrics(SM_CXSCREEN);
	size.mHeight = GetSystemMetrics(SM_CYSCREEN);
	return false;
}

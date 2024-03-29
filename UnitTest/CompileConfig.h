
#pragma once

#include "../WorkSpace/WorkSpace.h"
#include <string.h>

#if defined WIN64 || defined _WIN64
#	if defined DEBUG || defined _DEBUG
#		pragma comment(lib, "../x64/Debug/WorkSpace.lib")
#	else
#		pragma comment(lib, "../x64/Release/WorkSpace.lib")
#	endif
#else
#	if defined DEBUG || defined _DEBUG
#		pragma comment(lib, "../Debug/WorkSpace.lib")
#	else
#		pragma comment(lib, "../Release/WorkSpace.lib")
#	endif
#endif

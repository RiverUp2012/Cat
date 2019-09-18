
#pragma once

#include "../WorkSpace/GameLib.h"
#include "../WorkSpace/WinLib.h"
#include <Windows.h>

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

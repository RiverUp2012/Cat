
#pragma once

//-------------------------------------------------------------------------------
// MFC 相关配置
//-------------------------------------------------------------------------------

#ifndef VC_EXTRALEAN
#	define VC_EXTRALEAN
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _AFX_ALL_WARNINGS

#include <afxwin.h>
#include <afxext.h>

#ifndef _AFX_NO_OLE_SUPPORT
#	include <afxdtctl.h>
#endif

#ifndef _AFX_NO_AFXCMN_SUPPORT
#	include <afxcmn.h>
#endif

#include <afxcontrolbars.h>

//-------------------------------------------------------------------------------
// 标准 C 库相关配置
//-------------------------------------------------------------------------------

#include <string.h>
#include <wchar.h>

//-------------------------------------------------------------------------------
// STL 相关配置
//-------------------------------------------------------------------------------

#include <vector>
#include <list>
#include <string>

//-------------------------------------------------------------------------------
// GDI+ 相关配置
//-------------------------------------------------------------------------------

#pragma comment(lib, "gdiplus.lib")

//-------------------------------------------------------------------------------
// WorkSpace 相关配置
//-------------------------------------------------------------------------------

#include "../WorkSpace/WinLib.h"
#include "../WorkSpace/GameLib.h"

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


#pragma once

//-------------------------------------------------------------------------------
// MFC �������
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
// STL �������
//-------------------------------------------------------------------------------

#include <vector>

//-------------------------------------------------------------------------------
// GDI+ �������
//-------------------------------------------------------------------------------

#pragma comment(lib, "gdiplus.lib")

//-------------------------------------------------------------------------------
// WinLib �������
//-------------------------------------------------------------------------------

#include "../WinLib/Include/WinLib.h"

#if defined WIN64 || defined _WIN64
#	if defined DEBUG || defined _DEBUG
#		pragma comment(lib, "../x64/Debug/WinLib.lib")
#	else
#		pragma comment(lib, "../x64/Release/WinLib.lib")
#	endif
#else
#	if defined DEBUG || defined _DEBUG
#		pragma comment(lib, "../Debug/WinLib.lib")
#	else
#		pragma comment(lib, "../Release/WinLib.lib")
#	endif
#endif

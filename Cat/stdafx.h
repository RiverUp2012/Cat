
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
// TurboLib ʵ�ú������������
//-------------------------------------------------------------------------------

#include "../TurboLib/TurboLib.h"

#if defined WIN64 || defined _WIN64
#	if defined DEBUG || defined _DEBUG
#		pragma comment(lib, "../x64/Debug/TurboLib.lib")
#	else
#		pragma comment(lib, "../x64/Release/TurboLib.lib")
#	endif
#else
#	if defined DEBUG || defined _DEBUG
#		pragma comment(lib, "../Debug/TurboLib.lib")
#	else
#		pragma comment(lib, "../Release/TurboLib.lib")
#	endif
#endif

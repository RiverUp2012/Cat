
#include "../GameLibInclude/glWindow.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glException.h"
#include "../GameLibInclude/glGlobalData.h"

#define GL_WINDOW_CLASS_NAME (L"glWndCls")
#define GL_APP_INSTANCE (gGetModuleHandleW ? gGetModuleHandleW(0) : 0)

typedef HMODULE(WINAPI * glGetModuleHandleW)(
	LPCWSTR lpModuleName);
typedef VOID(WINAPI * glPostQuitMessage)(
	int nExitCode);
typedef LRESULT(WINAPI * glDefWindowProcW)(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam);
typedef int(WINAPI * glGetSystemMetrics)(
	int nIndex);
typedef HGDIOBJ(WINAPI * glGetStockObject)(
	int i);
typedef HCURSOR(WINAPI * glLoadCursorW)(
	HINSTANCE hInstance,
	LPCWSTR lpCursorName);
typedef BOOL(WINAPI * glAdjustWindowRectEx)(
	LPRECT lpRect,
	DWORD dwStyle,
	BOOL bMenu,
	DWORD dwExStyle);
typedef ATOM(WINAPI * glRegisterClassExW)(
	CONST WNDCLASSEXW *);
typedef BOOL(WINAPI * glIsWindow)(
	HWND hWnd);
typedef BOOL(WINAPI * glDestroyWindow)(
	HWND hWnd);
typedef HWND(WINAPI * glCreateWindowExW)(
	DWORD dwExStyle,
	LPCWSTR lpClassName,
	LPCWSTR lpWindowName,
	DWORD dwStyle,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu,
	HINSTANCE hInstance,
	LPVOID lpParam);
typedef BOOL(WINAPI * glUnregisterClassW)(
	LPCWSTR lpClassName,
	HINSTANCE hInstance);

namespace {
	static glGetModuleHandleW gGetModuleHandleW = 0;
	static glPostQuitMessage gPostQuitMessage = 0;
	static glDefWindowProcW gDefWindowProcW = 0;
	static glGetSystemMetrics gGetSystemMetrics = 0;
	static glGetStockObject gGetStockObject = 0;
	static glLoadCursorW gLoadCursorW = 0;
	static glAdjustWindowRectEx gAdjustWindowRectEx = 0;
	static glRegisterClassExW gRegisterClassExW = 0;
	static glIsWindow gIsWindow = 0;
	static glDestroyWindow gDestroyWindow = 0;
	static glCreateWindowExW gCreateWindowExW = 0;
	static glUnregisterClassW gUnregisterClassW = 0;
}

static LRESULT CALLBACK glWndMsgProc(
	HWND wndHandle,
	UINT wndMessage,
	WPARAM wParam,
	LPARAM lParam) {
	if (!gPostQuitMessage || !gDefWindowProcW) {
		throw glException(L"YOU !! RPWT ??");
	}
	if (WM_DESTROY == wndMessage) {
		gPostQuitMessage(0);
	}
	return gDefWindowProcW(wndHandle, wndMessage, wParam, lParam);
}

glWindow::glWindow() {
	if (!gModule_User32.isAlready()) {
		gModule_User32.createW(L"user32.dll");
	}
	if (!gModule_Kernel32.isAlready()) {
		gModule_Kernel32.createW(L"kernel32.dll");
	}
	if (!gModule_GDI32.isAlready()) {
		gModule_GDI32.createW(L"gdi32.dll");
	}
	if (gModule_Kernel32.isAlready()) {
		if (!gGetModuleHandleW) {
			gGetModuleHandleW = (glGetModuleHandleW)
				gModule_Kernel32.getProcAddressA("GetModuleHandleW");
		}
	}
	if (gModule_GDI32.isAlready()) {
		if (!gGetStockObject) {
			gGetStockObject = (glGetStockObject)
				gModule_GDI32.getProcAddressA("GetStockObject");
		}
	}
	if (gModule_User32.isAlready()) {
		if (!gPostQuitMessage) {
			gPostQuitMessage = (glPostQuitMessage)
				gModule_User32.getProcAddressA("PostQuitMessage");
		}
		if (!gDefWindowProcW) {
			gDefWindowProcW = (glDefWindowProcW)
				gModule_User32.getProcAddressA("DefWindowProcW");
		}
		if (!gGetSystemMetrics) {
			gGetSystemMetrics = (glGetSystemMetrics)
				gModule_User32.getProcAddressA("GetSystemMetrics");
		}
		if (!gLoadCursorW) {
			gLoadCursorW = (glLoadCursorW)
				gModule_User32.getProcAddressA("LoadCursorW");
		}
		if (!gAdjustWindowRectEx) {
			gAdjustWindowRectEx = (glAdjustWindowRectEx)
				gModule_User32.getProcAddressA("AdjustWindowRectEx");
		}
		if (!gRegisterClassExW) {
			gRegisterClassExW = (glRegisterClassExW)
				gModule_User32.getProcAddressA("RegisterClassExW");
		}
		if (!gIsWindow) {
			gIsWindow = (glIsWindow)
				gModule_User32.getProcAddressA("IsWindow");
		}
		if (!gDestroyWindow) {
			gDestroyWindow = (glDestroyWindow)
				gModule_User32.getProcAddressA("DestroyWindow");
		}
		if (!gCreateWindowExW) {
			gCreateWindowExW = (glCreateWindowExW)
				gModule_User32.getProcAddressA("CreateWindowExW");
		}
		if (!gUnregisterClassW) {
			gUnregisterClassW = (glUnregisterClassW)
				gModule_User32.getProcAddressA("UnregisterClassW");
		}
	}
	mWindowHandle = 0;
}

glWindow::~glWindow() {
	destroy();
}

bool glWindow::createW(
	const wchar_t * windowTitle,
	const int screenWidth,
	const int screenHeight) {
	bool ret = false;
	int desktopWidth = gGetSystemMetrics(SM_CXSCREEN);
	int desktopHeight = gGetSystemMetrics(SM_CYSCREEN);
	DWORD wndStyle = WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	DWORD wndStyleEx = WS_EX_ACCEPTFILES;
	RECT wndRect = { 0, 0, screenWidth, screenHeight };
	WNDCLASSEXW wndCls = { 0 };
	int wndWidth = 0;
	int wndHeight = 0;
	int wndX = 0;
	int wndY = 0;
	destroy();
	if (gRegisterClassExW && gAdjustWindowRectEx && gCreateWindowExW && gIsWindow) {
		wndCls.cbSize = sizeof(wndCls);
		wndCls.hbrBackground = (HBRUSH)gGetStockObject(BLACK_BRUSH);
		wndCls.hCursor = gLoadCursorW(0, MAKEINTRESOURCEW(32512));
		wndCls.lpfnWndProc = glWndMsgProc;
		wndCls.hInstance = GL_APP_INSTANCE;
		wndCls.lpszClassName = GL_WINDOW_CLASS_NAME;
		wndCls.style = CS_HREDRAW | CS_VREDRAW;
		if (gRegisterClassExW(&wndCls)) {
			if (gAdjustWindowRectEx(&wndRect, wndStyle, FALSE, wndStyleEx)) {
				wndWidth = wndRect.right - wndRect.left;
				wndHeight = wndRect.bottom - wndRect.top;
				wndX = (desktopWidth - wndWidth) / 2;
				wndY = (desktopHeight - wndHeight) / 2;
				mWindowHandle = (void *)gCreateWindowExW(
					wndStyleEx,
					GL_WINDOW_CLASS_NAME,
					windowTitle,
					wndStyle,
					wndX,
					wndY,
					wndWidth,
					wndHeight,
					0,
					0,
					GL_APP_INSTANCE,
					0);
				if (gIsWindow((HWND)mWindowHandle)) {
					ret = true;
				}
				else {
					throw glWin32APIException(L"CreateWindowExW", GetLastError());
				}
			}
			else {
				throw glWin32APIException(L"AdjustWindowRectEx", GetLastError());
			}
		}
		else {
			throw glWin32APIException(L"RegisterClassExW", GetLastError());
		}
	}
	return ret;
}

void glWindow::destroy(void) {
	if (gIsWindow && gIsWindow((HWND)mWindowHandle)) {
		gDestroyWindow((HWND)mWindowHandle);
	}
	if (gUnregisterClassW) {
		gUnregisterClassW(GL_WINDOW_CLASS_NAME, GL_APP_INSTANCE);
	}
	mWindowHandle = 0;
}

bool glWindow::isAlready(void) const {
	return mWindowHandle && gIsWindow && gIsWindow((HWND)mWindowHandle) ? true : false;
}

void * glWindow::getHandle(void) const {
	return mWindowHandle;
}

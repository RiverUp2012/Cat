
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

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

static LRESULT CALLBACK glWndMsgProc(
	HWND wndHandle,
	UINT wndMessage,
	WPARAM wParam,
	LPARAM lParam) {
	if (WM_DESTROY == wndMessage) {
		gPostQuitMessage(0);
	}
	return gDefWindowProcW(wndHandle, wndMessage, wParam, lParam);
}

glWindow::glWindow() {
	gModuleUser32.createW(L"user32.dll");
	gModuleKernel32.createW(L"kernel32.dll");
	gModuleGDI32.createW(L"gdi32.dll");	
	gGetModuleHandleW = (glGetModuleHandleW)
		gModuleKernel32.getProcAddressA("GetModuleHandleW");
	gPostQuitMessage = (glPostQuitMessage)
		gModuleUser32.getProcAddressA("PostQuitMessage");
	gDefWindowProcW = (glDefWindowProcW)
		gModuleUser32.getProcAddressA("DefWindowProcW");
	gGetSystemMetrics = (glGetSystemMetrics)
		gModuleUser32.getProcAddressA("GetSystemMetrics");
	gGetStockObject = (glGetStockObject)
		gModuleGDI32.getProcAddressA("GetStockObject");
	gLoadCursorW = (glLoadCursorW)
		gModuleUser32.getProcAddressA("LoadCursorW");
	gAdjustWindowRectEx = (glAdjustWindowRectEx)
		gModuleUser32.getProcAddressA("AdjustWindowRectEx");
	gRegisterClassExW = (glRegisterClassExW)
		gModuleUser32.getProcAddressA("RegisterClassExW");
	gIsWindow = (glIsWindow)
		gModuleUser32.getProcAddressA("IsWindow");
	gDestroyWindow = (glDestroyWindow)
		gModuleUser32.getProcAddressA("DestroyWindow");
	gCreateWindowExW = (glCreateWindowExW)
		gModuleUser32.getProcAddressA("CreateWindowExW");
	gUnregisterClassW = (glUnregisterClassW)
		gModuleUser32.getProcAddressA("UnregisterClassW");
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
		}
	}
	return ret;
}

void glWindow::destroy(void) {
	if (gIsWindow((HWND)mWindowHandle)) {
		gDestroyWindow((HWND)mWindowHandle);
		mWindowHandle = 0;
	}
	gUnregisterClassW(GL_WINDOW_CLASS_NAME, GL_APP_INSTANCE);
}

bool glWindow::isAlready(void) const {
	return mWindowHandle && gIsWindow((HWND)mWindowHandle);
}

void * glWindow::getHandle(void) const {
	return mWindowHandle;
}

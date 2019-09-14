
#include "../SurgeGameEngine.h"
#include "../Include/SurgeGameEnginePrivate.h"

#define SGE_WINDOW_CLASS_NAME (L"sgeWndCls")
#define SGE_APP_INSTANCE (gGetModuleHandleW ? gGetModuleHandleW(0) : 0)

typedef HMODULE(WINAPI * sgeGetModuleHandleW)(
	LPCWSTR lpModuleName);
typedef VOID(WINAPI * sgePostQuitMessage)(
	int nExitCode);
typedef LRESULT(WINAPI * sgeDefWindowProcW)(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam);
typedef int(WINAPI * sgeGetSystemMetrics)(
	int nIndex);
typedef HGDIOBJ(WINAPI * sgeGetStockObject)(
	int i);
typedef HCURSOR(WINAPI * sgeLoadCursorW)(
	HINSTANCE hInstance,
	LPCWSTR lpCursorName);
typedef BOOL(WINAPI * sgeAdjustWindowRectEx)(
	LPRECT lpRect,
	DWORD dwStyle,
	BOOL bMenu,
	DWORD dwExStyle);
typedef ATOM(WINAPI * sgeRegisterClassExW)(
	CONST WNDCLASSEXW *);
typedef BOOL(WINAPI * sgeIsWindow)(
	HWND hWnd);
typedef BOOL(WINAPI * sgeDestroyWindow)(
	HWND hWnd);
typedef HWND(WINAPI * sgeCreateWindowExW)(
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
typedef BOOL(WINAPI * sgeUnregisterClassW)(
	LPCWSTR lpClassName,
	HINSTANCE hInstance);

static sgeGetModuleHandleW gGetModuleHandleW = 0;
static sgePostQuitMessage gPostQuitMessage = 0;
static sgeDefWindowProcW gDefWindowProcW = 0;
static sgeGetSystemMetrics gGetSystemMetrics = 0;
static sgeGetStockObject gGetStockObject = 0;
static sgeLoadCursorW gLoadCursorW = 0;
static sgeAdjustWindowRectEx gAdjustWindowRectEx = 0;
static sgeRegisterClassExW gRegisterClassExW = 0;
static sgeIsWindow gIsWindow = 0;
static sgeDestroyWindow gDestroyWindow = 0;
static sgeCreateWindowExW gCreateWindowExW = 0;
static sgeUnregisterClassW gUnregisterClassW = 0;

static LRESULT CALLBACK sgeWndMsgProc(
	HWND wndHandle,
	UINT wndMessage,
	WPARAM wParam,
	LPARAM lParam)
{
	if (WM_DESTROY == wndMessage)
	{
		gPostQuitMessage(0);
	}

	return gDefWindowProcW(wndHandle, wndMessage, wParam, lParam);
}

sgeWindow::sgeWindow()
{
	gModuleUser32.createW(L"user32.dll");
	gModuleKernel32.createW(L"kernel32.dll");
	gModuleGDI32.createW(L"gdi32.dll");
	
	gGetModuleHandleW = (sgeGetModuleHandleW)
		gModuleKernel32.getProcAddressA("GetModuleHandleW");
	gPostQuitMessage = (sgePostQuitMessage)
		gModuleUser32.getProcAddressA("PostQuitMessage");
	gDefWindowProcW = (sgeDefWindowProcW)
		gModuleUser32.getProcAddressA("DefWindowProcW");
	gGetSystemMetrics = (sgeGetSystemMetrics)
		gModuleUser32.getProcAddressA("GetSystemMetrics");
	gGetStockObject = (sgeGetStockObject)
		gModuleGDI32.getProcAddressA("GetStockObject");
	gLoadCursorW = (sgeLoadCursorW)
		gModuleUser32.getProcAddressA("LoadCursorW");
	gAdjustWindowRectEx = (sgeAdjustWindowRectEx)
		gModuleUser32.getProcAddressA("AdjustWindowRectEx");
	gRegisterClassExW = (sgeRegisterClassExW)
		gModuleUser32.getProcAddressA("RegisterClassExW");
	gIsWindow = (sgeIsWindow)
		gModuleUser32.getProcAddressA("IsWindow");
	gDestroyWindow = (sgeDestroyWindow)
		gModuleUser32.getProcAddressA("DestroyWindow");
	gCreateWindowExW = (sgeCreateWindowExW)
		gModuleUser32.getProcAddressA("CreateWindowExW");
	gUnregisterClassW = (sgeUnregisterClassW)
		gModuleUser32.getProcAddressA("UnregisterClassW");

	mWindowHandle = 0;
}

sgeWindow::~sgeWindow()
{
	destroy();
}

bool sgeWindow::createW(
	const wchar_t * windowTitle,
	const int screenWidth,
	const int screenHeight)
{
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
	wndCls.lpfnWndProc = sgeWndMsgProc;
	wndCls.hInstance = SGE_APP_INSTANCE;
	wndCls.lpszClassName = SGE_WINDOW_CLASS_NAME;
	wndCls.style = CS_HREDRAW | CS_VREDRAW;

	if (gRegisterClassExW(&wndCls))
	{
		if (gAdjustWindowRectEx(&wndRect, wndStyle, FALSE, wndStyleEx))
		{
			wndWidth = wndRect.right - wndRect.left;
			wndHeight = wndRect.bottom - wndRect.top;
			wndX = (desktopWidth - wndWidth) / 2;
			wndY = (desktopHeight - wndHeight) / 2;

			mWindowHandle = (void *)gCreateWindowExW(
				wndStyleEx,
				SGE_WINDOW_CLASS_NAME,
				windowTitle,
				wndStyle,
				wndX,
				wndY,
				wndWidth,
				wndHeight,
				0,
				0,
				SGE_APP_INSTANCE,
				0);
			if (gIsWindow((HWND)mWindowHandle))
			{
				ret = true;
			}
		}
	}

	return ret;
}

void sgeWindow::destroy(void)
{
	if (gIsWindow((HWND)mWindowHandle))
	{
		gDestroyWindow((HWND)mWindowHandle);
		mWindowHandle = 0;
	}

	gUnregisterClassW(SGE_WINDOW_CLASS_NAME, SGE_APP_INSTANCE);
}

bool sgeWindow::isAlready(void) const
{
	return mWindowHandle && gIsWindow((HWND)mWindowHandle);
}

void * sgeWindow::getHandle(void) const
{
	return mWindowHandle;
}

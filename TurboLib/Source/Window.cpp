
#include "../TurboLib.h"
#include "../Include/Private.h"

#define T_WND_CLASS_NAME (L"TWndClsW")
#define T_APP_HANDLE (GetModuleHandleW(0))
#define T_MAX_WINDOW (64)

typedef struct _T_WINDOW
{
	HWND mWindowHandle;
	TWindowEventCallbackProc mEventProc;
}
T_WINDOW;

static ATOM gWindowClassAtom = 0;
static T_WINDOW gWindowArray[T_MAX_WINDOW] = { 0 };
static int gValidWindowCount = 0;

static T_WINDOW * TFindUnuseWindow(void)
{
	for (int i = 0; i < T_MAX_WINDOW; ++i)
	{
		if (!IsWindow(gWindowArray[i].mWindowHandle))
		{
			return &gWindowArray[i];
		}
	}

	return 0;
}

static T_WINDOW * TFindWindowByHWND(
	const HWND wndHandle)
{
	for (int i = 0; i < T_MAX_WINDOW; ++i)
	{
		if (wndHandle == gWindowArray[i].mWindowHandle)
		{
			return &gWindowArray[i];
		}
	}

	return 0;
}

static LRESULT CALLBACK TGlobalWindowMessageProc(
	HWND wndHandle,
	UINT wndMessage,
	WPARAM wParam,
	LPARAM lParam)
{
	T_WINDOW * windowImpl = TFindWindowByHWND(wndHandle);

	if (WM_DESTROY == wndMessage)
	{
		PostQuitMessage(0);
	}
	else if (WM_NCDESTROY == wndMessage)
	{
		T_WINDOW * windowImpl = TFindWindowByHWND(wndHandle);
		if (windowImpl)
		{
			windowImpl->mWindowHandle = 0;
			--gValidWindowCount;
		}
	}
	else if (WM_MOUSEMOVE == wndMessage)
	{

	}
	else if (WM_LBUTTONUP == wndMessage)
	{

	}
	else if (WM_LBUTTONDOWN == wndMessage)
	{

	}
	else if (WM_RBUTTONUP == wndMessage)
	{

	}
	else if (WM_RBUTTONDOWN == wndMessage)
	{

	}
	else if (WM_MOUSEWHEEL == wndMessage)
	{

	}
	else if (WM_KEYUP == wndMessage)
	{

	}
	else if (WM_KEYDOWN == wndMessage)
	{

	}
	else if (WM_CHAR == wndMessage)
	{

	}

	return DefWindowProcW(wndHandle, wndMessage, wParam, lParam);
}

T_OBJECT TWindowCreateW(
	const wchar_t * windowTitle,
	const int clientWidth,
	const int clientHeight,
	const int showNow)
{
	WNDCLASSEXW wndCls = { 0 };
	RECT wndRect = { 0 };
	DWORD wndStyle = 0;
	DWORD wndStyleEx = 0;

	if (!gWindowClassAtom)
	{
		wndCls.cbSize = sizeof(wndCls);
		wndCls.hInstance = T_APP_HANDLE;
		wndCls.lpfnWndProc = TGlobalWindowMessageProc;
		wndCls.lpszClassName = T_WND_CLASS_NAME;
		wndCls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndCls.hCursor = LoadCursor(0, IDC_ARROW);
		wndCls.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

		gWindowClassAtom = RegisterClassExW(&wndCls);
	}

	T_WINDOW * windowImpl = TFindUnuseWindow();
	if (windowImpl)
	{
		if (gWindowClassAtom)
		{
			wndRect.right = clientWidth;
			wndRect.bottom = clientHeight;

			wndStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
			wndStyleEx = WS_EX_ACCEPTFILES;

			if (AdjustWindowRectEx(&wndRect, wndStyle, FALSE, wndStyleEx))
			{
				windowImpl->mWindowHandle = CreateWindowExW(
					wndStyleEx,
					wndCls.lpszClassName,
					windowTitle,
					wndStyle,
					0,
					0,
					wndRect.right - wndRect.left,
					wndRect.bottom - wndRect.top,
					0,
					0,
					GetModuleHandleW(0),
					0);
				if (IsWindow(windowImpl->mWindowHandle))
				{
					if (showNow)
					{
						ShowWindow(windowImpl->mWindowHandle, SW_SHOW);
						UpdateWindow(windowImpl->mWindowHandle);
					}

					++gValidWindowCount;
					return (T_OBJECT)windowImpl;
				}
			}
		}
	}

	return 0;
}

T_OBJECT TWindowCreateA(
	const char * windowTitle,
	const int clientWidth,
	const int clientHeight,
	const int showNow)
{
	T_OBJECT window = 0;
	wchar_t * windowTitleW = 0;

	if (windowTitle)
	{
		windowTitleW = TStringA2W(windowTitle);
	}

	window = TWindowCreateW(
		windowTitleW,
		clientWidth,
		clientHeight,
		showNow);

	if (windowTitleW)
	{
		TFree(windowTitleW);
		windowTitleW = 0;
	}

	return window;
}

void TWindowDestroy(
	T_OBJECT window)
{
	T_WINDOW * windowImpl = (T_WINDOW *)window;
	if (windowImpl)
	{
		if (IsWindow(windowImpl->mWindowHandle))
		{
			DestroyWindow(windowImpl->mWindowHandle);
			windowImpl->mWindowHandle = 0;
		}

		if (gWindowClassAtom)
		{
			UnregisterClassW(T_WND_CLASS_NAME, T_APP_HANDLE);
			gWindowClassAtom = 0;
		}

		windowImpl->mEventProc = 0;
	}
}

int TWindowShow(
	T_OBJECT window,
	const int showOrHide)
{
	T_WINDOW * windowImpl = (T_WINDOW *)window;
	if (windowImpl && IsWindow(windowImpl->mWindowHandle))
	{
		ShowWindow(windowImpl->mWindowHandle, showOrHide ? SW_SHOW : SW_HIDE);

		return T_TRUE;
	}

	return T_FALSE;
}

int TWindowProcessMessage(void)
{
	MSG msg = { 0 };

	if (gValidWindowCount > 0)
	{
		if (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
			{
				return T_FALSE;
			}

			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		return T_TRUE;
	}

	return T_FALSE;
}

void TWindowWaitMessage(void)
{
	WaitMessage();
}

int TWindowIsValid(
	T_OBJECT window)
{
	T_WINDOW * windowImpl = (T_WINDOW *)window;
	if (windowImpl)
	{
		if (IsWindow(windowImpl->mWindowHandle))
		{
			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TWindowPutDesktopCenter(
	T_OBJECT window)
{
	int desktopWidth = 0;
	int desktopHeight = 0;
	RECT wndRect = { 0 };

	T_WINDOW * windowImpl = (T_WINDOW *)window;
	if (windowImpl)
	{
		if (GetWindowRect(windowImpl->mWindowHandle, &wndRect))
		{
			desktopWidth = GetSystemMetrics(SM_CXSCREEN);
			desktopHeight = GetSystemMetrics(SM_CYSCREEN);

			if (MoveWindow(
				windowImpl->mWindowHandle,
				(desktopWidth - (wndRect.right - wndRect.left)) / 2,
				(desktopHeight - (wndRect.bottom - wndRect.top)) / 2,
				wndRect.right - wndRect.left,
				wndRect.bottom - wndRect.top,
				FALSE))
			{
				return T_TRUE;
			}
		}
	}

	return T_FALSE;
}

void TWindowSetEventCallback(
	T_OBJECT window,
	TWindowEventCallbackProc eventProc)
{
	T_WINDOW * windowImpl = (T_WINDOW *)window;
	if (windowImpl)
	{
		windowImpl->mEventProc = eventProc;
	}
}

TWindowEventCallbackProc TWindowGetEventCallback(
	T_OBJECT window)
{
	T_WINDOW * windowImpl = (T_WINDOW *)window;
	
	return windowImpl ? windowImpl->mEventProc : 0;
}

HWND TWindowGetHandle(
	T_OBJECT window)
{
	T_WINDOW * windowImpl = (T_WINDOW *)window;

	return windowImpl ? windowImpl->mWindowHandle : 0;
}

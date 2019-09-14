
//
// @file WinLib.h
// @brief Windows 编程工具库
// @desc 用于辅助 Windows 操作系统下的编程开发
// @author 李远兵
// @date 2019-09-12
//

#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <gdiplus.h>
#include <stdarg.h>
#include <list>
#include <string>

//
// @brief 不可复制基类
// @desc 任何继承自该类的子类，都将不可复制，若执行复制操作，将引起编译错误
//
class wlNonCopyable {
public:
	wlNonCopyable();
	wlNonCopyable(const wlNonCopyable & other) = delete;
	virtual ~wlNonCopyable();
public:
	wlNonCopyable & operator = (const wlNonCopyable & other) = delete;
};

//
// @brief
//
class wlLog {
public:
	static bool openW(const wchar_t * logFileName);
	static void close(void);
	static bool putMessageW(const wchar_t * format, ...);
	static bool putMessageA(const char * format, ...);
};

class wlFile : public wlNonCopyable {
public:
	wlFile();
	virtual ~wlFile();
public:
	bool openW(const wchar_t * fileName, const bool forRead, const bool forWrite);
	void close(void);
private:
	HANDLE mFileHandle = 0;
};

//
// @brief 互斥类
// @desc 用于线程资源同步
//
class wlMutex : public wlNonCopyable {
public:
	wlMutex();
	virtual ~wlMutex();
public:
	void lock(void);
	void unlock(void);
private:
	CRITICAL_SECTION mCriticalSection;
};

//
// @brief 代码域互斥哨兵
// @desc 在生命期内自动同步线程资源
//
class wlMutexGuard : public wlNonCopyable {
public:
	wlMutexGuard(wlMutex * mutex);
	virtual ~wlMutexGuard();
private:
	wlMutex * mMutex = 0;
};

//
// @brief 事件类
//
class wlEvent : public wlNonCopyable {
public:
	wlEvent();
	virtual ~wlEvent();
public:
	bool createW(const wchar_t * eventName, const bool manualReset, const bool initState);
	bool openW(const wchar_t * eventName);
	void destroy(void);
private:
	HANDLE mEventHandle = 0;
};

//
// @brief 线程类
//
class wlThread : public wlNonCopyable {
public:
	wlThread();
	virtual ~wlThread();
public:
	bool create(const bool runNow = true);
	void destroy(const int waitTimeout = 0);
	bool isAlready(void) const;
public:
	virtual void onThreadRun(void) = 0;
private:
	HANDLE mThreadHandle = 0;
	DWORD mThreadID = 0;
};

//
// @brief 进程特性枚举体
//
enum wlProcessFeature {
	// 终止进程
	WL_PROCESS_FEATURE_TERMINATE = (1 << 0),
	// 查询进程信息
	WL_PROCESS_FEATURE_QUERY_INFO = (1 << 2),
};

//
// @brief 进程类
//
class wlProcess : public wlNonCopyable {
public:
	wlProcess();
	virtual ~wlProcess();
public:
	bool openByProcessID(const DWORD processID, const int features = 0);
	void close(void);
	bool terminate(void);
	bool getImageFileNameW(std::wstring & imageFileName);
private:
	HANDLE mProcessHandle = 0;
};

//
// @brief 进程枚举回调接口类
//
class wlProcessEnumCallback {
public:
	virtual bool onEnumProcess(const DWORD processID) = 0;
};

//
// @brief 进程工具类
//
class wlProcessHelper {
public:
	static void enumProcess(wlProcessEnumCallback * callback);
};

//
// @brief 进程枚举接口包装类
//
class wlProcessEnumCallbackWarpper : public wlProcessEnumCallback, public wlNonCopyable {
public:
	wlProcessEnumCallbackWarpper();
	virtual ~wlProcessEnumCallbackWarpper();
public:
	void enumProcess(void);
	const std::list<DWORD> & getProcessIDList(void) const;
private:
	bool onEnumProcess(const DWORD processID) override;
private:
	std::list<DWORD> mProcessIDList;
};

//
// @brief 模块类
//
class wlModule : public wlNonCopyable {
public:
	wlModule();
	virtual ~wlModule();
public:
	bool loadW(const wchar_t * moduleFileName);
	void unload(void);
	bool isAlready(void) const;
	void * getProcAddressA(const char * procName);
private:
	HMODULE mModuleHandle = 0;
};

//
// @brief 字符串工具类
//
class wlStringHelper {
public:
	static bool a2w(const char * stringA, std::wstring & stringW, const bool toUTF8 = false);
	static bool w2a(const wchar_t * stringW, std::string & stringA, const bool toUTF8 = false);
	static bool formatW(const wchar_t * format, const va_list & vl, std::wstring & string);
	static bool formatA(const char * format, const va_list & vl, std::string & string);
};

//
// @brief 用于保证应用程序只有一个实例正在运行的类
//
class wlSingleAppInstance : public wlNonCopyable {
public:
	wlSingleAppInstance();
	virtual ~wlSingleAppInstance();
public:
	bool checkW(const wchar_t * appInstanceName);
private:
	wlEvent mEvent;
};

//
// @brief 路径工具类
//
class wlPathHelper {
public:
	static bool getFileNameWithExtW(const wchar_t * path, std::wstring & fileNameWithExt);
	static bool getAppPathW(std::wstring & appPath);
};

//
// @brief 文件工具类
//
class wlFileHelper {
public:
	static bool deleteFileW(const wchar_t * fileName);
};

//
// @brief GDI 位图类
//
class wlGDIBitmap : public wlNonCopyable {
public:
	wlGDIBitmap();
	virtual ~wlGDIBitmap();
public:
	bool createEmpty(const int width, const int height, const int bitCount);
	void destroy(void);
	const HBITMAP & getHBITMAP(void) const;
private:
	HBITMAP mBitmapHandle = 0;
};

//
// @brief GDI DC 类
//
class wlGDIDC : public wlNonCopyable {
public:
	wlGDIDC();
	virtual ~wlGDIDC();
public:
	bool createFromHDC(const HDC & dcHandle);
	bool createFromDC(const wlGDIDC & dc);
	bool createFromHWND(const HWND & wndHandle);
	void destroy(void);
	void selectBitmap(wlGDIBitmap & bitmap);
	const HDC & getHDC(void) const;
private:
	HWND mWndHandle = 0;
	HDC mDCHandle = 0;
};

//
// @brief GDI+ 图像类
//
class wlGDIPImage : public wlNonCopyable {
public:
	wlGDIPImage();
	virtual ~wlGDIPImage();
public:
	bool createFromFileW(const wchar_t * fileName);
	void destroy(void);
	int getWidth(void) const;
	int getHeight(void) const;
	Gdiplus::Image * getImage(void) const;
private:
	Gdiplus::Image * mImage = 0;
};

//
// @brief GDI+ 窗口类
//
class wlGDIPWindow : public wlNonCopyable {
public:
	wlGDIPWindow();
	virtual ~wlGDIPWindow();
public:
	bool createFromHWND(const HWND & wndHandle);
	void destroy(void);
	const wlGDIDC & getDC(void) const;
	bool present(void);
	bool drawImage(wlGDIPImage & image, const int x, const int y, const int width, const int height);
private:
	wlGDIDC mBackBufferDC;
	wlGDIBitmap mBackBufferBitmap;
	Gdiplus::Graphics * mGraphics = 0;
	HWND mWndHandle = 0;
	wlGDIDC mClientDC;
};

//
// @brief GDI+ 启动类
// @desc 用于自动启动与关闭 GDI+ 库
//
class wlGDIPStartup final : public wlNonCopyable {
public:
	wlGDIPStartup();
	~wlGDIPStartup();
private:
	ULONG_PTR mToken = 0;
};

class wlInputHandler {
public:
	virtual bool onMouseMove(const int mouseX, const int mouseY) { return true; }
	virtual bool onKeyUp(const int keyCode) { return true; }
	virtual bool onKeyDown(const int keyCode) { return true; }
	virtual bool onMouseWhellUp(void) { return true; }
	virtual bool onMouseWhellDown(void) { return true; }
};

class wlGDIPUIWindows : public wlInputHandler, public wlGDIPWindow {
public:
	wlGDIPUIWindows();
	virtual ~wlGDIPUIWindows();
public:
private:
};

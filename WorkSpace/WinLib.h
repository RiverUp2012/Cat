
//
// @file WinLib.h
// @brief Windows 编程工具库
// @desc 用于辅助 Windows 操作系统下的编程开发
// @author 李远兵
// @date 2019-09-12
//

#pragma once

#include <stdarg.h>
#include "GameLibTemplate.h"

#define WL_FORMAT_W(_Format, _String, _Ret) \
{ \
if (_Format) \
{ \
	va_list vl = { 0 }; \
	va_start(vl, _Format); \
	_Ret = wlStringHelper::formatW(_Format, vl, _String); \
	va_end(vl); \
} \
}

#define WL_FORMAT_A(_Format, _String, _Ret) \
{ \
if (_Format) \
{ \
	va_list vl = { 0 }; \
	va_start(vl, _Format); \
	_Ret = wlStringHelper::formatA(_Format, vl, _String); \
	va_end(vl); \
} \
}

//
// @brief 不可复制基类
// @desc 任何继承自该类的子类，都将不可复制，若执行复制操作，将引起编译错误
//
class wlNonCopyable {
public:
	wlNonCopyable();
	virtual ~wlNonCopyable();
private:
	wlNonCopyable(const wlNonCopyable & other);
	wlNonCopyable & operator = (const wlNonCopyable & other);
};

//
// @brief 日志类
//
class wlLog {
public:
	static bool openW(const wchar_t * logFileName);
	static void close(void);
	static bool putMessageW(const wchar_t * format, ...);
	static bool putMessageA(const char * format, ...);
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
	void * mCriticalSection;
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
	void * mEventHandle;
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
	void * mThreadHandle ;
	unsigned long mThreadID = 0;
};

//
// @brief 进程特性枚举体
//
enum wlProcessFeature {
	// 终止进程
	WL_PROCESS_FEATURE_TERMINATE = (1 << 0),
	// 查询进程信息
	WL_PROCESS_FEATURE_QUERY_INFO = (1 << 2),
	// 操纵进程虚拟内存
	WL_PROCESS_FEATURE_VM_OPERATION = (1 << 3),
};

//
// @brief 进程类
//
class wlProcess : public wlNonCopyable {
public:
	wlProcess();
	virtual ~wlProcess();
public:
	bool openByProcessID(const unsigned long processID, const int features = 0);
	void close(void);
	bool terminate(void);
	bool getImageFileNameW(glStringW & imageFileName);
	bool vmRead(const void * vmAddress, void * buffer, const int bytesToRead);
	bool vmWrite(void * vmAddress, const void * buffer, const int bytesToWrite);
	bool setPrivilegeW(const wchar_t * privilegeName, const bool enableOrDisable);
private:
	void * mProcessHandle;
};

//
// @brief 进程枚举回调接口类
//
class wlProcessEnumCallback {
public:
	virtual bool onEnumProcessW(
		const unsigned long processID,
		const wchar_t * exeFileName) = 0;
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
	struct wlProcessInfo {
		unsigned long mProcessID;
		glStringW mExeFileName;
	};
public:
	wlProcessEnumCallbackWarpper();
	virtual ~wlProcessEnumCallbackWarpper();
public:
	void enumProcess(void);
	const glList<wlProcessInfo> & getProcessInfoList(void) const;
private:
	bool onEnumProcessW(
		const unsigned long processID,
		const wchar_t * exeFileName) override;
private:
	glList<wlProcessInfo> mProcessInfoList;
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
	void * mModuleHandle;
};

//
// @brief 字符串工具类
//
class wlStringHelper {
public:
	static bool a2w(const char * stringA, glStringW & stringW, const bool toUTF8 = false);
	static bool w2a(const wchar_t * stringW, glStringA & stringA, const bool toUTF8 = false);
	static bool formatW(const wchar_t * format, const va_list & vl, glStringW & string);
	static bool formatA(const char * format, const va_list & vl, glStringA & string);
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
	static bool getFileNameWithExtW(const wchar_t * path, glStringW & fileNameWithExt);
	static bool getAppPathW(glStringW & appPath);
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
	const void * getHBITMAP(void) const;
private:
	void * mBitmapHandle;
};

//
// @brief GDI DC 类
//
class wlGDIDC : public wlNonCopyable {
public:
	wlGDIDC();
	virtual ~wlGDIDC();
public:
	bool createFromHDC(const void * dcHandle);
	bool createFromDC(const wlGDIDC & dc);
	bool createFromHWND(const void * wndHandle);
	void destroy(void);
	void selectBitmap(wlGDIBitmap & bitmap);
	const void * getHDC(void) const;
private:
	void * mWndHandle;
	void * mDCHandle;
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
	void * getImage(void) const;
private:
	void * mImage;
};

//
// @brief GDI+ 窗口类
//
class wlGDIPWindow : public wlNonCopyable {
public:
	wlGDIPWindow();
	virtual ~wlGDIPWindow();
public:
	bool createFromHWND(const void * wndHandle);
	void destroy(void);
	const wlGDIDC & getDC(void) const;
	bool present(void);
	bool drawImage(wlGDIPImage & image, const int x, const int y, const int width, const int height);
private:
	wlGDIDC mBackBufferDC;
	wlGDIBitmap mBackBufferBitmap;
	void * mGraphics;
	void * mWndHandle;
	wlGDIDC mClientDC;
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

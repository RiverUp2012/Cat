
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
#include <list>
#include <string>

namespace wl {

	//
	// @brief 不可复制基类
	// @desc 任何继承自该类的子类，都将不可复制，若执行复制操作，将引起编译错误
	//
	class NonCopyable {
	public:
		NonCopyable();
		NonCopyable(const NonCopyable & other) = delete;
		virtual ~NonCopyable();
	public:
		NonCopyable & operator = (const NonCopyable & other) = delete;
	};

	//
	// @brief 互斥类
	// @desc 用于线程资源同步
	//
	class Mutex : public NonCopyable {
	public:
		Mutex();
		virtual ~Mutex();
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
	class MutexGuard : public NonCopyable {
	public:
		MutexGuard(Mutex * mutex);
		virtual ~MutexGuard();
	private:
		Mutex * mMutex = 0;
	};

	//
	// @brief 事件类
	//
	class Event : public NonCopyable {
	public:
		Event();
		virtual ~Event();
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
	class Thread : public NonCopyable {
	public:
		Thread();
		virtual ~Thread();
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
	enum ProcessFeature {
		// 终止进程
		PROCESS_FEATURE_TERMINATE = (1 << 0),
		// 查询进程信息
		PROCESS_FEATURE_QUERY_INFO = (1 << 2),
	};

	//
	// @brief 进程类
	//
	class Process : public NonCopyable {
	public:
		Process();
		virtual ~Process();
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
	class ProcessEnumCallback {
	public:
		virtual bool onEnumProcess(const DWORD processID) = 0;
	};

	//
	// @brief 进程工具类
	//
	class ProcessHelper {
	public:
		static void enumProcess(ProcessEnumCallback * callback);
	};

	//
	// @brief 进程枚举接口包装类
	//
	class ProcessEnumCallbackWarpper : public ProcessEnumCallback, public NonCopyable {
	public:
		ProcessEnumCallbackWarpper();
		virtual ~ProcessEnumCallbackWarpper();
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
	class Module : public NonCopyable {
	public:
		Module();
		virtual ~Module();
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
	class StringHelper {
	public:
		static bool a2w(const char * stringA, std::wstring & stringW, const bool toUTF8 = false);
		static bool w2a(const wchar_t * stringW, std::string & stringA, const bool toUTF8 = false);
	};

	//
	// @brief 用于保证应用程序只有一个实例正在运行的类
	//
	class SingleAppInstance : public NonCopyable {
	public:
		SingleAppInstance();
		virtual ~SingleAppInstance();
	public:
		bool checkW(const wchar_t * appInstanceName);
	private:
		Event mEvent;
	};

	//
	// @brief 路径工具类
	//
	class PathHelper {
	public:
		static bool getFileNameWithExtW(const wchar_t * path, std::wstring & fileNameWithExt);
		static bool getAppPathW(std::wstring & appPath);
	};

	//
	// @brief 文件工具类
	//
	class FileHelper {
	public:
		static bool deleteFileW(const wchar_t * fileName);
	};

	//
	// @brief GDI 位图类
	//
	class GDIBitmap : public NonCopyable {
	public:
		GDIBitmap();
		virtual ~GDIBitmap();
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
	class GDIDC : public NonCopyable {
	public:
		GDIDC();
		virtual ~GDIDC();
	public:
		bool createFromHDC(const HDC & dcHandle);
		bool createFromDC(const GDIDC & dc);
		bool createFromHWND(const HWND & wndHandle);
		void destroy(void);
		void selectBitmap(GDIBitmap & bitmap);
		const HDC & getHDC(void) const;
	private:
		HWND mWndHandle = 0;
		HDC mDCHandle = 0;
	};

	//
	// @brief GDI+ 图像类
	//
	class GDIPImage : public NonCopyable {
	public:
		GDIPImage();
		virtual ~GDIPImage();
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
	class GDIPWindow : public NonCopyable {
	public:
		GDIPWindow();
		virtual ~GDIPWindow();
	public:
		bool createFromHWND(const HWND & wndHandle);
		void destroy(void);
		const GDIDC & getDC(void) const;
		bool present(void);
		bool drawImage(GDIPImage & image, const int x, const int y, const int width, const int height);
	private:
		GDIDC mBackBufferDC;
		GDIBitmap mBackBufferBitmap;
		Gdiplus::Graphics * mGraphics = 0;
		HWND mWndHandle = 0;
		GDIDC mClientDC;
	};

	//
	// @brief GDI+ 启动类
	// @desc 用于自动启动与关闭 GDI+ 库
	//
	class GDIPStartup final : public NonCopyable {
	public:
		GDIPStartup();
		~GDIPStartup();
	private:
		ULONG_PTR mToken = 0;
	};

} // namespace wl

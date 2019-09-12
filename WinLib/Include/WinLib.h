
//
// @file WinLib.h
// @brief Windows ��̹��߿�
// @desc ���ڸ��� Windows ����ϵͳ�µı�̿���
// @author ��Զ��
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
	// @brief ���ɸ��ƻ���
	// @desc �κμ̳��Ը�������࣬�������ɸ��ƣ���ִ�и��Ʋ�����������������
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
	// @brief ������
	// @desc �����߳���Դͬ��
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
	// @brief �����򻥳��ڱ�
	// @desc �����������Զ�ͬ���߳���Դ
	//
	class MutexGuard : public NonCopyable {
	public:
		MutexGuard(Mutex * mutex);
		virtual ~MutexGuard();
	private:
		Mutex * mMutex = 0;
	};

	//
	// @brief �¼���
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
	// @brief �߳���
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
	// @brief ��������ö����
	//
	enum ProcessFeature {
		// ��ֹ����
		PROCESS_FEATURE_TERMINATE = (1 << 0),
		// ��ѯ������Ϣ
		PROCESS_FEATURE_QUERY_INFO = (1 << 2),
	};

	//
	// @brief ������
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
	// @brief ����ö�ٻص��ӿ���
	//
	class ProcessEnumCallback {
	public:
		virtual bool onEnumProcess(const DWORD processID) = 0;
	};

	//
	// @brief ���̹�����
	//
	class ProcessHelper {
	public:
		static void enumProcess(ProcessEnumCallback * callback);
	};

	//
	// @brief ����ö�ٽӿڰ�װ��
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
	// @brief ģ����
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
	// @brief �ַ���������
	//
	class StringHelper {
	public:
		static bool a2w(const char * stringA, std::wstring & stringW, const bool toUTF8 = false);
		static bool w2a(const wchar_t * stringW, std::string & stringA, const bool toUTF8 = false);
	};

	//
	// @brief ���ڱ�֤Ӧ�ó���ֻ��һ��ʵ���������е���
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
	// @brief ·��������
	//
	class PathHelper {
	public:
		static bool getFileNameWithExtW(const wchar_t * path, std::wstring & fileNameWithExt);
		static bool getAppPathW(std::wstring & appPath);
	};

	//
	// @brief �ļ�������
	//
	class FileHelper {
	public:
		static bool deleteFileW(const wchar_t * fileName);
	};

	//
	// @brief GDI λͼ��
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
	// @brief GDI DC ��
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
	// @brief GDI+ ͼ����
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
	// @brief GDI+ ������
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
	// @brief GDI+ ������
	// @desc �����Զ�������ر� GDI+ ��
	//
	class GDIPStartup final : public NonCopyable {
	public:
		GDIPStartup();
		~GDIPStartup();
	private:
		ULONG_PTR mToken = 0;
	};

} // namespace wl

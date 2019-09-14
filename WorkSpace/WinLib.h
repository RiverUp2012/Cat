
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
#include <stdarg.h>
#include "SurgeGameEngineTemplate.h"

//
// @brief ���ɸ��ƻ���
// @desc �κμ̳��Ը�������࣬�������ɸ��ƣ���ִ�и��Ʋ�����������������
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
// @brief
//
class wlLog {
public:
	static bool openW(const wchar_t * logFileName);
	static void close(void);
	static bool putMessageW(const wchar_t * format, ...);
	static bool putMessageA(const char * format, ...);
};

//
// @brief ������
// @desc �����߳���Դͬ��
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
// @brief �����򻥳��ڱ�
// @desc �����������Զ�ͬ���߳���Դ
//
class wlMutexGuard : public wlNonCopyable {
public:
	wlMutexGuard(wlMutex * mutex);
	virtual ~wlMutexGuard();
private:
	wlMutex * mMutex = 0;
};

//
// @brief �¼���
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
// @brief �߳���
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
// @brief ��������ö����
//
enum wlProcessFeature {
	// ��ֹ����
	WL_PROCESS_FEATURE_TERMINATE = (1 << 0),
	// ��ѯ������Ϣ
	WL_PROCESS_FEATURE_QUERY_INFO = (1 << 2),
};

//
// @brief ������
//
class wlProcess : public wlNonCopyable {
public:
	wlProcess();
	virtual ~wlProcess();
public:
	bool openByProcessID(const DWORD processID, const int features = 0);
	void close(void);
	bool terminate(void);
	bool getImageFileNameW(sgeStringW & imageFileName);
private:
	void * mProcessHandle;
};

//
// @brief ����ö�ٻص��ӿ���
//
class wlProcessEnumCallback {
public:
	virtual bool onEnumProcess(const unsigned long processID) = 0;
};

//
// @brief ���̹�����
//
class wlProcessHelper {
public:
	static void enumProcess(wlProcessEnumCallback * callback);
};

//
// @brief ����ö�ٽӿڰ�װ��
//
class wlProcessEnumCallbackWarpper : public wlProcessEnumCallback, public wlNonCopyable {
public:
	wlProcessEnumCallbackWarpper();
	virtual ~wlProcessEnumCallbackWarpper();
public:
	void enumProcess(void);
	const sgeList<unsigned long> & getProcessIDList(void) const;
private:
	bool onEnumProcess(const unsigned long processID) override;
private:
	sgeList<unsigned long> mProcessIDList;
};

//
// @brief ģ����
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
// @brief �ַ���������
//
class wlStringHelper {
public:
	static bool a2w(const char * stringA, sgeStringW & stringW, const bool toUTF8 = false);
	static bool w2a(const wchar_t * stringW, sgeStringA & stringA, const bool toUTF8 = false);
	static bool formatW(const wchar_t * format, const va_list & vl, sgeStringW & string);
	static bool formatA(const char * format, const va_list & vl, sgeStringA & string);
};

//
// @brief ���ڱ�֤Ӧ�ó���ֻ��һ��ʵ���������е���
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
// @brief ·��������
//
class wlPathHelper {
public:
	static bool getFileNameWithExtW(const wchar_t * path, sgeStringW & fileNameWithExt);
	static bool getAppPathW(sgeStringW & appPath);
};

//
// @brief �ļ�������
//
class wlFileHelper {
public:
	static bool deleteFileW(const wchar_t * fileName);
};

//
// @brief GDI λͼ��
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
// @brief GDI DC ��
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
// @brief GDI+ ͼ����
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
// @brief GDI+ ������
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

//
// @brief GDI+ ������
// @desc �����Զ�������ر� GDI+ ��
//
class wlGDIPStartup final : public wlNonCopyable {
public:
	wlGDIPStartup();
	~wlGDIPStartup();
private:
	ULONG_PTR mToken;
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
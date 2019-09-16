
//
// @file WinLib.h
// @brief Windows ��̹��߿�
// @desc ���ڸ��� Windows ����ϵͳ�µı�̿���
// @author ��Զ��
// @date 2019-09-12
//

#pragma once

#include <stdarg.h>
#include "GameLib.h"

//
// @brief ��������ö����
//
enum wlProcessFeature {
	// ��ֹ����
	WL_PROCESS_FEATURE_TERMINATE = (1 << 0),
	// ��ѯ������Ϣ
	WL_PROCESS_FEATURE_QUERY_INFO = (1 << 2),
	// ���ݽ��������ڴ�
	WL_PROCESS_FEATURE_VM_OPERATION = (1 << 3),
};

//
// @brief ������
//
class wlProcess : public glNonCopyable {
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
	void * getProcessHandle(void) const;
	unsigned long getProcesseID(void) const;
private:
	void * mProcessHandle;
	unsigned long mProcessID;
};

//
// @brief ����ö�ٻص��ӿ���
//
class wlProcessEnumCallback {
public:
	virtual bool onEnumProcessW(
		const unsigned long processID,
		const wchar_t * exeFileName) = 0;
};

//
// @brief ģ��ö�ٻص��ӿ���
//
class wlModuleEnumCallback {
public:
	virtual bool onEnumModuleW(
		const wchar_t * moduleFileName,
		void * moduleHandle) = 0;
};

//
// @brief ���̹�����
//
class wlProcessHelper {
public:
	static void enumProcess(wlProcessEnumCallback * callback);
	static void enumModule(const unsigned long processId, wlModuleEnumCallback * callback);
};

//
// @brief ����ö�ٽӿڰ�װ��
//
class wlProcessEnumCallbackWarpper : public wlProcessEnumCallback, public glNonCopyable {
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
// @brief ģ��ö�ٽӿڰ�װ��
//
class wlModuleEnumCallbackWarpper : public wlModuleEnumCallback, public glNonCopyable {
public:
	struct wlModuleInfo {
		void * mModuleHandle;
		glStringW mModuleFileName;
	};
public:
	wlModuleEnumCallbackWarpper();
	virtual ~wlModuleEnumCallbackWarpper();
public:
	void enumModule(const unsigned long processId);
	const glList<wlModuleInfo> & getModuleInfoList(void) const;
private:
	bool onEnumModuleW(
		const wchar_t * moduleFileName,
		void * moduleHandle) override;
private:
	glList<wlModuleInfo> mModuleInfoList;
};

//
// @brief GDI λͼ��
//
class wlGDIBitmap : public glNonCopyable {
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
class wlGDIDC : public glNonCopyable {
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
class wlGDIPImage : public glNonCopyable {
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
class wlGDIPWindow : public glNonCopyable {
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


//
// @file GameLib.h
// @brief Windows ��Ϸ��̹��߿�
// @desc ���ڸ��� Windows ����ϵͳ�µ���Ϸ��̿���
// @author ��Զ��
// @date 2019-09-12
//

#pragma once

#include <stdarg.h>
#include "GameLibTemplate.h"

//
// @brief ��ȡ����ʱ��С��֪����������
//
#define GL_DIM(_Array) (sizeof(_Array) / sizeof(_Array[0]))

//
// @brief ��ʽ���ַ���
//
#define GL_FORMAT_W(_Format, _String, _Ret) \
{ \
if (_Format) \
{ \
	va_list vl = { 0 }; \
	va_start(vl, _Format); \
	_Ret = glStringHelper::formatW(_Format, vl, _String); \
	va_end(vl); \
} \
}

//
// @brief ��ʽ���ַ���
//
#define GL_FORMAT_A(_Format, _String, _Ret) \
{ \
if (_Format) \
{ \
	va_list vl = { 0 }; \
	va_start(vl, _Format); \
	_Ret = glStringHelper::formatA(_Format, vl, _String); \
	va_end(vl); \
} \
}

//
// @brief ��������ö����
//
enum glInputType {
	// ��������
	glInputTypeKeyDown,
	// ��������
	glInputTypeKeyUp,
	// ����ƶ�
	glInputTypeMouseMove,
};

//
// @brief ���ɸ��ƻ���
//
class glNonCopyable {
public:
	glNonCopyable();
	virtual ~glNonCopyable();
private:
	glNonCopyable(const glNonCopyable & other);
	glNonCopyable & operator = (const glNonCopyable & other);
};

//
// @brief ���ü�������
//
class glRefCounter {
public:
	glRefCounter();
	virtual ~glRefCounter();
public:
	void addRef(void);
	bool release(void);
	int getRefCount(void) const;
private:
	int mRefCount;
};

//
// @brief ��Ϸ״̬��
//
class glGameState : public glRefCounter {
public:
	glGameState();
	virtual ~glGameState();
public:
	virtual void onCreate(void);
	virtual void onDestroy(void);
	virtual void onEnter(void);
	virtual void onLeave(void);
	virtual void onUpdate(const float frameElapse);
	virtual void onPaint(void);
};

//
// @brief �ɻ��ƶ�����
//
class glPaintObject {
public:
	glPaintObject();
	virtual ~glPaintObject();
public:
	void setPos(const glPoint<float> & pos);
	const glPoint<float> & getPos(void) const;
	void setSize(const glSize<float> & size);
	const glSize<float> & getSize(void) const;
	glRect<float> getBoundBox(void) const;
	void setVisible(const bool visible);
	bool getVisible(void) const;
public:
	virtual void onPaint(const glPoint<float> & parentPos);
private:
	glPoint<float> mPos;
	glSize<float> mSize;
	bool mVisible;
};

//
// @brief ���봦������
//
class glInputHandler {
public:
	glInputHandler();
	virtual ~glInputHandler();
public:
	void setHandleInputEvent(const bool handleInputEvent);
	bool getHandleInputEvent(void) const;
public:
	virtual bool handleInput(
		const glInputType inputType,
		const glPoint<int> & mousePos,
		const int keyCode);
private:
	bool mHandleInputEvent;
};

//
// @brief ������
//
class glTexture : public glNonCopyable {
public:
	glTexture();
	virtual ~glTexture();
public:
	bool createFromFileW(
		const wchar_t * fileName,
		const unsigned int colorKey = 0);
	void destroy(void);
	bool isAlready(void) const;
	const glSize<float> & getImageSize(void) const;
	const glSize<float> & getSurfaceSize(void) const;
	void * getIDirect3DTexture9(void) const;
	const wchar_t * getImageFileNameW(void) const;
private:
	void * mD3DTex9;
	glSize<float> mImageSize;
	glSize<float> mSurfaceSize;
	glStringW mImageFileName;
};

//
// @brief ������
//
class glSprite : public glNonCopyable {
public:
	glSprite();
	glSprite(glTexture * texture);
	virtual ~glSprite();
public:
	bool createFromTexture(glTexture * texture);
	void destroy(void);
	const glSize<float> & getImageSize(void) const;
	bool paint(void);
	bool paint(
		const glRect<float> & paintRect,
		const glRect<float> & textureRect,
		const unsigned int diffuse = 0xffffffff);
private:
	void * mD3DTex9;
	glSize<float> mImageSize;
	glSize<float> mSurfaceSize;
};

//
// @brief ������
//
class glFont : public glNonCopyable {
public:
	glFont();
	virtual ~glFont();
public:
	bool createW(
		const wchar_t * fontName,
		const int fontWidth,
		const int fontHeight);
	void destroy(void);
	bool paintTextW(
		const wchar_t * text,
		const int charsToPaint,
		const glRect<int> & paintRect,
		const unsigned int paintFormat,
		const unsigned int color);
	bool calcTextSizeW(
		const wchar_t * text,
		const int charsToCalc,
		const glSize<int> & layoutSize,
		const unsigned int calcFormat,
		glSize<int> & textSize);
private:
	void * mD3DXFont;
};

//
// @brief ������
//
class glSound : public glNonCopyable {
public:
	glSound();
	virtual ~glSound();
public:
	bool createFromWaveFileW(const wchar_t * fileName);
	bool create(
		const unsigned short channels,
		const unsigned short bitsPerSample,
		const unsigned int sampleRate,
		const unsigned int bufferSize);
	void destroy(void);
	void * lock(const int offset, const int size);
	bool unlock(void * audioPtr, const int size);
	bool play(const bool loop);
	bool stop(void);
	bool setVolume(const float volume);
	bool getVolume(float & volume);
	bool isPlaying(bool & playing);
private:
	void * mDSBuf8;
};

//
// @brief �ļ���
//
class glFile : public glNonCopyable {
public:
	glFile();
	virtual ~glFile();
public:
	bool openW(
		const wchar_t * fileName,
		const bool forRead,
		const bool forWrite);
	bool openA(
		const char * fileName,
		const bool forRead,
		const bool forWrite);
	void close(void);
	bool isAlready(void) const;
	bool seekToBegin(void);
	bool seekToEnd(void);
	bool seekTo(const long long int pos);
	bool seekOffset(const long long int offset);
	bool getPointer(long long int & pointer);
	bool getFileSize(long long int & fileSize);
	bool write(const void * data, const int bytesToWrite);
	bool read(void * data, const int bytesToRead);
private:
	void * mFileHandle;
};

//
// @brief ģ����
//
class glModule : public glNonCopyable {
public:
	glModule();
	glModule(const wchar_t * moduleFileName);
	virtual ~glModule();
public:
	bool createW(const wchar_t * moduleFileName);
	void destroy(void);
	bool isAlready(void) const;
	void * getProcAddressW(const wchar_t * procName);
	void * getProcAddressA(const char * procName);
private:
	void * mModuleHandle;
};

//
// @brief ������
//
class glEngine : public glNonCopyable {
public:
	static glEngine * get(void);
public:
	glEngine();
	virtual ~glEngine();
public:
	void go(
		const wchar_t * windowTitle,
		const int screenWidth,
		const int screenHeight);
public:
	void pushGameState(glGameState * gameState);
	void popGameState(void);
	void popAllGameState(void);
	glGameState * getRunningGameState(void);
public:
	bool paintPoint(
		const glPoint<float> & pos,
		const unsigned int color);
	bool paintLine(
		const glPoint<float> & posStart,
		const glPoint<float> & posEnd,
		const unsigned int color);
	bool paintTriangle(
		const glPoint<float> & pt1,
		const glPoint<float> & pt2,
		const glPoint<float> & pt3,
		const unsigned int color,
		const bool solid);
	bool paintRectangle(
		const glPoint<float> & pos,
		const glSize<float> & size,
		const unsigned int color,
		const bool solid);
public:
	bool isKeyDown(const int keyCode) const;
public:
	virtual bool onCreate(void);
	virtual void onDestroy(void);
private:
	unsigned char mKeysStateArray[256];
	glList<glGameState *> mGameStateList;
};

//
// @brief �ַ���������
//
class glStringHelper {
public:
	static bool a2w(const char * stringA, glStringW & stringW, const bool toUTF8 = false);
	static bool w2a(const wchar_t * stringW, glStringA & stringA, const bool toUTF8 = false);
	static int findA(const char * string, const char * subString);
	static int findW(const wchar_t * string, const wchar_t * subString);
	static bool formatW(const wchar_t * format, const va_list & vl, glStringW & string);
	static bool formatA(const char * format, const va_list & vl, glStringA & string);
};

//
// @brief ��־��
//
class glLog {
public:
	static bool createW(const wchar_t * logFileName);
	static void destroy(void);
	static void setOutputDebugView(const bool outputDebugView);
	static bool putMessageW(const wchar_t * format, ...);
	static bool putMessageA(const char * format, ...);
};

//
// @brief ������
// @desc �����߳���Դͬ��
//
class glMutex : public glNonCopyable {
public:
	glMutex();
	virtual ~glMutex();
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
class glMutexGuard : public glNonCopyable {
public:
	glMutexGuard(glMutex * mutex);
	virtual ~glMutexGuard();
private:
	glMutex * mMutex = 0;
};

//
// @brief �¼���
//
class glEvent : public glNonCopyable {
public:
	glEvent();
	virtual ~glEvent();
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
class glThread : public glNonCopyable {
public:
	glThread();
	virtual ~glThread();
public:
	bool create(const bool runNow = true);
	void destroy(const int waitTimeout = 0);
	bool isAlready(void) const;
public:
	virtual void onThreadRun(void) = 0;
private:
	void * mThreadHandle;
	unsigned long mThreadID = 0;
};

//
// @brief ���ڱ�֤Ӧ�ó���ֻ��һ��ʵ���������е���
//
class glSingleAppInstance : public glNonCopyable {
public:
	glSingleAppInstance();
	virtual ~glSingleAppInstance();
public:
	bool checkW(const wchar_t * appInstanceName);
private:
	glEvent mEvent;
};

//
// @brief ·��������
//
class glPathHelper {
public:
	static bool getFileNameWithExtW(const wchar_t * path, glStringW & fileNameWithExt);
	static bool getAppPathW(glStringW & appPath);
};

//
// @brief �ļ�������
//
class glFileHelper {
public:
	static bool deleteFileW(const wchar_t * fileName);
};

//
// @brief �첽����ӿ���
//
class glAsyncTask : public glRefCounter {
public:
	virtual void onAsyncTaskRun(void) = 0;
};

//
// @brief �첽���������
//
class glAsyncTaskQueue {
public:
	static void postTask(glAsyncTask * task);
	static void quit(void);
};
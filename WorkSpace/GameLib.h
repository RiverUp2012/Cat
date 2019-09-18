
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
// @brief ʱ��ṹ��
//
struct glTime {
	unsigned int mYear;
	unsigned int mMonth;
	unsigned int mDay;
	unsigned int mHour;
	unsigned int mMinute;
	unsigned int mSecond;
	unsigned int mMilliseconds;
};

//
// @brief �ڴ���Ϣ�ṹ��
//
struct glMemoryInfo {
	unsigned long long int mPhysTotal;
	unsigned long long int mPhysAvail;
	unsigned long long int mVirtualTotal;
	unsigned long long int mVirtualAvail;
};

//
// @brief �쳣��
//
class glException {
public:
	glException();
	glException(const wchar_t * message);
	virtual ~glException();
public:
	const wchar_t * getMessage(void) const;
protected:
	wchar_t mMessage[520];
};

//
// @brief Win32 API �쳣��
//
class glWin32APIException : public glException {
public:
	glWin32APIException();
	glWin32APIException(const wchar_t * win32APIName, const unsigned int win32LastError);
	virtual ~glWin32APIException();
public:
	unsigned int getWin32LastError(void) const;
protected:
	unsigned int mWin32LastError;
};

//
// @brief COM API �쳣��
//
class glCOMAPIException : public glException {
public:
	glCOMAPIException();
	glCOMAPIException(const wchar_t * comAPIName, const long comRet);
	virtual ~glCOMAPIException();
public:
	long getComRet(void) const;
protected:
	long mComRet;
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
	virtual bool onMouseMove(const int mouseX, const int mouseY);
	virtual bool onKeyUp(const int keyCode);
	virtual bool onKeyDown(const int keyCode);
	virtual bool onMouseWhellUp(void);
	virtual bool onMouseWhellDown(void);
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
	bool createFromMemory(
		const void * buffer,
		const unsigned int bufferSize,
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
	bool isEndOfFile(bool & endOfFile);
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
// @brief ��ʱ���ӿ���
//
class glTimer {
public:
	glTimer();
	virtual ~glTimer();
public:
	bool registerTimer(const int timerID, const int duration);
	bool unregisterTimer(const int timerID);
	bool unregisterTimer(void);
public:
	virtual void onTimer(const int timerID) = 0;
};

//
// @brief ��ʱ��ϵͳ��
//
class glTimerSystem {
public:
	static bool registerTimer(glTimer * timer, const int timerID, const int duration);
	static bool unregisterTimer(glTimer * timer, const int timerID);
	static bool unregisterTimer(glTimer * timer);
	static void quit(void);
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
	bool wait(const int waitTimeout);
	bool isAlready(void) const;
	void sleep(const int sleepTimeOut);
public:
	virtual void onThreadRun(void) = 0;
private:
	void * mThreadHandle;
	unsigned long mThreadID = 0;
};

//
// @brief ���ڱ�֤Ӧ�ó���ֻ��һ��ʵ���������е���
//
class glSingleAppInstanceChecker : public glNonCopyable {
public:
	glSingleAppInstanceChecker();
	virtual ~glSingleAppInstanceChecker();
public:
	bool checkSingleAppInstanceW(const wchar_t * appInstanceName);
private:
	glEvent mEvent;
};

//
// @brief ·��������
//
class glPathHelper {
public:
	static bool getFileNameWithExtW(const wchar_t * path, glStringW & fileNameWithExt);
	static bool getDriveW(const wchar_t * path, glStringW & drive);
	static bool getAppPathW(glStringW & appPath);
	static void pathAppendSlashW(glStringW & path);
	static void createPathW(const wchar_t * path);
};

//
// @brief �ļ�ö�ٴ�����
//
class glFileEnumHandler {
public:
	virtual bool onFileEnumW(
		const wchar_t * filePath,
		const wchar_t * fileName,
		const bool isDirectory) = 0;
};

//
// @brief �ļ�������
//
class glFileHelper {
public:
	static bool deleteFileW(const wchar_t * fileName);
	static void enumFileW(
		const wchar_t * path,
		const wchar_t * fileExt,
		glFileEnumHandler * enumHandler);
};

//
// @brief �첽����ӿ���
// @desc
// ������Ҫ�����ں�̨�Ĵ�������������Լ̳��Ը����ͨ�� glAsyncTaskQueue
// ����е��ȣ���� glAsyncTaskCompleteCallback �ӿ��Ի�ȡ�첽���������Ϣ
// �����ʵ���У�������ֱ�ӱ��� glAsyncTaskCompleteCallback �ӿ�ʵ�������ǽ�
// glAsyncTaskCompleteCallback �ӿ�ʵ������� glAsyncTaskCompleteCallbackResourcePool
// ֮�У�����Ҫ��ʱ���ٴ� glAsyncTaskCompleteCallbackResourcePool ȡ����ʹ��
// ���磺
//
// class MyTask : public glAsyncTask {
// public:
//     MyTask(const int completeCallbackID) {
//         mCompleteCallbackID = completeCallbackID;
//     }
// public:
//     void onAsyncTaskRun(void) override {
//         // �����ﴦ���첽����
//         // ...
//         // �첽��������ϣ�ִ����ɻص�
//         glAsyncTaskCompleteCallback * completeCallback = 0;
//         glAsyncTaskCompleteCallbackResourcePool::getResource(
//             mCompleteCallbackID,
//             completeCallback,
//             true);
//         if(completeCallback) {
//             completeCallback->onAsyncTaskComplete();
//         }
//     }
// private:
//     int mCompleteCallbackID;
// };
//
// class MyCompleteCallback : public glAsyncTaskCompleteCallback {
// public:
//     ~MyCompleteCallback() {
//         // ���첽������ɻص�ʵ������Դ�����Ƴ�
//         glAsyncTaskCompleteCallbackResourcePool::markResourceUnuse(
//             this);
//     }
// public:
//     void onAsyncTaskComplete(void) override {
//         // �����ﴦ���첽������ɻص�
//     }
// };
//
// int main(int argc, char * argv[]) {
//     //
//     // �첽������ɻص�ʵ�� id
//     //
//     int callbackID = 0;
//     //
//     // �����첽������ɻص�ʵ��
//     //
//     MyCompleteCallback * callback = new MyCompleteCallback();
//     //
//     // ���첽������ɻص�ʵ���������Դ�أ�����ȡ��Ӧ�� id
//     //
//     glAsyncTaskCompleteCallbackResourcePool::insertResource(
//         callback,
//         callbackID);
//     //
//     // �����첽���񣬲����첽������ɻص�ʵ�� id ���ݸ��첽����
//     //
//     MyTask * task = new MyTask(callbackID);
//     //
//     // ���첽����Ͷ�뵽��������У��ȴ�������
//     //
//     glAsyncTaskQueue::postTask(task);
//     task->release();
//     //
//     // �������κ�ʱ�̣��㶼�������� callback ����task ���󲻻��ܵ��κ�Ӱ��
//     // ��� callback ������ task ��������첽����֮ǰ�����٣��� task ������ò���
//     // callback ���󣬶��޷�ִ����ɻص���������������Ԥ�ڵ����ý��
//     // ��� callback ������ task ��������첽����֮�����٣��� task ��������õ�
//     // callback ���󣬲�ִ����ɻص���������������Ԥ�ڵ���ѽ��
//     //
//     return 0;
// }
//
// �ⶫ��ΪʲôҪд����ô�����أ�����Ϊ���Ҹ��˹�������Ŀ���У�����������ôһ�����⣺
//
// task ������� callback ����ָ�룬�� task ���֮ǰ��callback ������Ѿ��� delete ���ˣ�
// ��� task ����֮ǰ�õ��� callback ���󣨴�ʱ�Ѿ������ٵ������е��õ�ʱ�򣬳���� crash ���ˡ�
//
// ���ԣ�������汾�У���������һ���м��� resource pool��callback �Ƿ����� resource pool
// ����ģ�������һ����һ�޶��� id ָ�� resource pool �е���� callback��task �ֳ� callback
// �� id���������κ�ʱ�򣬶�����ͨ����� callback id �� resource pool ��ѯ��Ӧ�� callback��
//
// ���� callback �������������ٵ�ʱ�򣬻Ὣ�Լ��� resource pool ���Ƴ���������һ����task ��ͨ�� id
// �� resource pool �в�ѯ callback ��ʱ�򣬾ͻ��ѯʧ�ܣ������˳��� crash ��������֡�
//
class glAsyncTask : public glRefCounter {
public:
	virtual void onAsyncTaskRun(void) = 0;
};

//
// @brief �첽������ɻص��ӿ���
//
class glAsyncTaskCompleteCallback {
public:
	virtual void onAsyncTaskComplete(void) = 0;
};

//
// @brief �첽������ɻص��ӿ���Դ��
//
class glAsyncTaskCompleteCallbackResourcePool {
public:
	static bool insertResource(
		glAsyncTaskCompleteCallback * const & resource,
		int & id);
	static bool getResource(
		const int id,
		glAsyncTaskCompleteCallback * & resource,
		const bool markResourceUnuse = true);
	static bool markResourceUnuse(
		glAsyncTaskCompleteCallback * const & resource);
};

//
// @brief �첽���������
//
class glAsyncTaskQueue {
public:
	static void postTask(glAsyncTask * task);
	static void quit(void);
};

//
// @brief ���� Socket ��
//
class glSocket : public glNonCopyable {
public:
	glSocket();
private:
	glSocket(const int socket);
public:
	virtual ~glSocket();
public:
	bool createForClient(void);
	bool createForServerA(const char * ipV4, const short int port);
	void destroy(void);
	bool connectToServerA(const char * ipV4, const short int port);
	bool sendData(const void * buffer, const int bytesToSend, int * bytesSended);
	bool recvData(void * buffer, const int bytesToRecv, int * bytesRecved);
private:
	int mSocket;
	bool mClientSocket;
	bool mServerSocket;
};

//
// @brief ��������
//
class glCmdLine {
public:
	static bool getParamByIndexW(const int index, glStringW & param);
	static bool isParamExistW(const wchar_t * param, int * index);
	static bool getSwitchValueW(const wchar_t * switchName, glStringW & value);
};

//
// @brief ��Ԫ���Ժ���
//
typedef void(*glUnitTestProc)(void);

//
// @brief ��Ԫ������
//
class glUnitTest {
public:
	static void pushUnitTestProcW(const wchar_t * caseName, glUnitTestProc testProc);
	static void runAllTestCase(void);
};

//
// @brief ������Ԫ���Է�֧
//
#define GL_TEST_CASE(_CaseName) \
extern void GL_TEST_PROC_##_CaseName(); \
class glTestRunner_##_CaseName \
{ \
public: \
glTestRunner_##_CaseName() \
{ \
glUnitTest::pushUnitTestProcW(L#_CaseName, GL_TEST_PROC_##_CaseName); \
} \
}; \
static glTestRunner_##_CaseName gTestRunner; \
void GL_TEST_PROC_##_CaseName()

//
// @brief ģ����Դ������
//
class glModuleResourceHelper {
public:
	struct glResourceInfo {
		void * mData;
		int mSize;
	};
public:
	static bool getResourceW(
		const int resourceID,
		const wchar_t * resourceType,
		glResourceInfo & resourceInfo);
};

//
// @brief ����������
//
class glDesktopHelper {
public:
	static bool getDesktopSize(glSize<int> & size);
};

//
// @brief ʱ��������
//
class glTimeHelper {
public:
	static bool getTimeElapseFromSystemStartup(unsigned int & timeElapse);
	static bool getTimeElapseFromSystemStartup64(unsigned long long int & timeElapse);
	static bool getLocalTime(glTime & localTime);
};

//
// @brief ϵͳ������
//
class glSystemHelper {
public:
	static bool getCurrentUserNameW(glStringW & userName);
	static bool getSystemDirectoryW(glStringW & systemDir);
	static bool getWindowDirectoryW(glStringW & windowDir);
	static bool getComputerNameW(glStringW & computerName);
	static bool getMemoryInfo(glMemoryInfo & memoryInfo);
};

//
// @brief ������������
//
class glDriveHelper {
public:
	static void getDriveNameListW(glArray<glStringW> & driveNameArray);
};

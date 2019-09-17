
//
// @file GameLib.h
// @brief Windows 游戏编程工具库
// @desc 用于辅助 Windows 操作系统下的游戏编程开发
// @author 李远兵
// @date 2019-09-12
//

#pragma once

#include <stdarg.h>
#include "GameLibTemplate.h"

//
// @brief 求取编译时大小已知的数组容量
//
#define GL_DIM(_Array) (sizeof(_Array) / sizeof(_Array[0]))

//
// @brief 格式化字符串
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
// @brief 格式化字符串
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
// @brief 输入类型枚举体
//
enum glInputType {
	// 按键按下
	glInputTypeKeyDown,
	// 按键弹起
	glInputTypeKeyUp,
	// 鼠标移动
	glInputTypeMouseMove,
};

//
// @brief 异常类
//
class glException {
public:
	glException(const wchar_t * message);
	glException(const unsigned int win32LastError);
	virtual ~glException();
public:
	const wchar_t * getMessage(void) const;
	unsigned int getWin32LastError(void) const;
private:
	const wchar_t * mMessage;
	unsigned int mWin32LastError;
};

//
// @brief 不可复制基类
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
// @brief 引用计数器类
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
// @brief 游戏状态类
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
// @brief 可绘制对象类
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
// @brief 输入处理器类
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
// @brief 纹理类
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
// @brief 精灵类
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
// @brief 字体类
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
// @brief 声音类
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
// @brief 文件类
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
// @brief 模块类
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
// @brief 引擎类
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
// @brief 字符串助手类
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
// @brief 日志类
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
// @brief 互斥类
// @desc 用于线程资源同步
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
// @brief 代码域互斥哨兵
// @desc 在生命期内自动同步线程资源
//
class glMutexGuard : public glNonCopyable {
public:
	glMutexGuard(glMutex * mutex);
	virtual ~glMutexGuard();
private:
	glMutex * mMutex = 0;
};

//
// @brief 事件类
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
// @brief 定时器接口类
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
// @brief 定时器系统类
//
class glTimerSystem {
public:
	static bool registerTimer(glTimer * timer, const int timerID, const int duration);
	static bool unregisterTimer(glTimer * timer, const int timerID);
	static bool unregisterTimer(glTimer * timer);
	static void quit(void);
};

//
// @brief 线程类
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
// @brief 用于保证应用程序只有一个实例正在运行的类
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
// @brief 路径工具类
//
class glPathHelper {
public:
	static bool getFileNameWithExtW(const wchar_t * path, glStringW & fileNameWithExt);
	static bool getAppPathW(glStringW & appPath);
};

//
// @brief 文件工具类
//
class glFileHelper {
public:
	static bool deleteFileW(const wchar_t * fileName);
};

//
// @brief 异步任务接口类
// @desc
// 所有需要放置于后台的处理操作，都可以继承自该类后，通过 glAsyncTaskQueue
// 类进行调度，配合 glAsyncTaskCompleteCallback 接口以获取异步任务完成信息
// 在最佳实践中，不建议直接保存 glAsyncTaskCompleteCallback 接口实例，而是将
// glAsyncTaskCompleteCallback 接口实例存放于 glAsyncTaskCompleteCallbackResourcePool
// 之中，有需要的时候，再从 glAsyncTaskCompleteCallbackResourcePool 取出来使用
// 比如：
//
// class MyTask : public glAsyncTask {
// public:
//     MyTask(const int completeCallbackID) {
//         mCompleteCallbackID = completeCallbackID;
//     }
// public:
//     void onAsyncTaskRun(void) override {
//         // 在这里处理异步任务
//         // ...
//         // 异步任务处理完毕，执行完成回调
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
//         // 将异步任务完成回调实例从资源池中移除
//         glAsyncTaskCompleteCallbackResourcePool::markResourceUnuse(
//             this);
//     }
// public:
//     void onAsyncTaskComplete(void) override {
//         // 在这里处理异步任务完成回调
//     }
// };
//
// int main(int argc, char * argv[]) {
//     //
//     // 异步任务完成回调实例 id
//     //
//     int callbackID = 0;
//     //
//     // 创建异步任务完成回调实例
//     //
//     MyCompleteCallback * callback = new MyCompleteCallback();
//     //
//     // 将异步任务完成回调实例存放于资源池，并获取对应的 id
//     //
//     glAsyncTaskCompleteCallbackResourcePool::insertResource(
//         callback,
//         callbackID);
//     //
//     // 创建异步任务，并将异步任务完成回调实例 id 传递给异步任务
//     //
//     MyTask * task = new MyTask(callbackID);
//     //
//     // 将异步任务投入到任务队列中，等待被调度
//     //
//     glAsyncTaskQueue::postTask(task);
//     task->release();
//     //
//     // 在随后的任何时刻，你都可以销毁 callback 对象，task 对象不会受到任何影响
//     // 如果 callback 对象在 task 对象完成异步任务之前被销毁，则 task 对象会拿不到
//     // callback 对象，而无法执行完成回调，这正是我们所预期的良好结果
//     // 如果 callback 对象在 task 对象完成异步任务之后被销毁，则 task 对象可以拿到
//     // callback 对象，并执行完成回调，这正是我们所预期的最佳结果
//     //
//     return 0;
// }
//
// 这东西为什么要写得这么复杂呢？是因为在我个人过往的项目当中，曾经遇到这么一个问题：
//
// task 对象持有 callback 对象指针，在 task 完成之前，callback 对象就已经被 delete 掉了，
// 随后 task 调用之前拿到的 callback 对象（此时已经被销毁掉）进行调用的时候，程序就 crash 掉了。
//
// 所以，在这个版本中，我引入了一个中间人 resource pool，callback 是放置在 resource pool
// 里面的，并且有一个独一无二的 id 指向 resource pool 中的这个 callback，task 手持 callback
// 的 id，并且在任何时候，都可以通过这个 callback id 向 resource pool 查询对应的 callback。
//
// 由于 callback 对象自身在销毁的时候，会将自己从 resource pool 中移除掉，这样一来，task 再通过 id
// 从 resource pool 中查询 callback 的时候，就会查询失败，避免了程序 crash 的情况出现。
//
class glAsyncTask : public glRefCounter {
public:
	virtual void onAsyncTaskRun(void) = 0;
};

//
// @brief 异步任务完成回调接口类
//
class glAsyncTaskCompleteCallback {
public:
	virtual void onAsyncTaskComplete(void) = 0;
};

//
// @brief 异步任务完成回调接口资源池
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
// @brief 异步任务队列类
//
class glAsyncTaskQueue {
public:
	static void postTask(glAsyncTask * task);
	static void quit(void);
};

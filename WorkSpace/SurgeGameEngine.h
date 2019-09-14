
#pragma once

#include "SurgeGameEngineTemplate.h"

#define SGE_DIM(_Array) (sizeof(_Array) / sizeof(_Array[0]))

enum sgeInputType
{
	sgeInputTypeKeyDown,
	sgeInputTypeKeyUp,
	sgeInputTypeMouseMove,
};

class sgeNonCopyable
{
public:
	sgeNonCopyable();
	virtual ~sgeNonCopyable();
private:
	sgeNonCopyable(const sgeNonCopyable & other);
	sgeNonCopyable & operator = (const sgeNonCopyable & other);
};

class sgeRefCounter
{
public:
	sgeRefCounter();
	virtual ~sgeRefCounter();
public:
	void addRef(void);
	bool release(void);
	int getRefCount(void) const;
private:
	int mRefCount;
};

class sgeGameState : public sgeRefCounter
{
public:
	sgeGameState();
	virtual ~sgeGameState();
public:
	virtual void onCreate(void);
	virtual void onDestroy(void);
	virtual void onEnter(void);
	virtual void onLeave(void);
	virtual void onUpdate(const float frameElapse);
	virtual void onPaint(void);
};

class sgePaintObject
{
public:
	sgePaintObject();
	virtual ~sgePaintObject();
public:
	void setPos(const sgePoint<float> & pos);
	const sgePoint<float> & getPos(void) const;
	void setSize(const sgeSize<float> & size);
	const sgeSize<float> & getSize(void) const;
	sgeRect<float> getBoundBox(void) const;
	void setVisible(const bool visible);
	bool getVisible(void) const;
public:
	virtual void onPaint(const sgePoint<float> & parentPos);
private:
	sgePoint<float> mPos;
	sgeSize<float> mSize;
	bool mVisible;
};

class sgeInputHandler
{
public:
	sgeInputHandler();
	virtual ~sgeInputHandler();
public:
	void setHandleInputEvent(const bool handleInputEvent);
	bool getHandleInputEvent(void) const;
public:
	virtual bool handleInput(
		const sgeInputType inputType,
		const sgePoint<int> & mousePos,
		const int keyCode);
private:
	bool mHandleInputEvent;
};

class sgeTexture : public sgeNonCopyable
{
public:
	sgeTexture();
	virtual ~sgeTexture();
public:
	bool createFromFileW(
		const wchar_t * fileName,
		const unsigned int colorKey = 0);
	void destroy(void);
	bool isAlready(void) const;
	const sgeSize<float> & getImageSize(void) const;
	const sgeSize<float> & getSurfaceSize(void) const;
	void * getIDirect3DTexture9(void) const;
	const wchar_t * getImageFileNameW(void) const;
private:
	void * mD3DTex9;
	sgeSize<float> mImageSize;
	sgeSize<float> mSurfaceSize;
	sgeStringW mImageFileName;
};

class sgeSprite : public sgeNonCopyable
{
public:
	sgeSprite();
	sgeSprite(sgeTexture * texture);
	virtual ~sgeSprite();
public:
	bool createFromTexture(sgeTexture * texture);
	void destroy(void);
	const sgeSize<float> & getImageSize(void) const;
	bool paint(void);
	bool paint(
		const sgeRect<float> & paintRect,
		const sgeRect<float> & textureRect,
		const unsigned int diffuse = 0xffffffff);
private:
	void * mD3DTex9;
	sgeSize<float> mImageSize;
	sgeSize<float> mSurfaceSize;
};

class sgeFont : public sgeNonCopyable
{
public:
	sgeFont();
	virtual ~sgeFont();
public:
	bool createW(
		const wchar_t * fontName,
		const int fontWidth,
		const int fontHeight);
	void destroy(void);
	bool paintTextW(
		const wchar_t * text,
		const int charsToPaint,
		const sgeRect<int> & paintRect,
		const unsigned int paintFormat,
		const unsigned int color);
	bool calcTextSizeW(
		const wchar_t * text,
		const int charsToCalc,
		const sgeSize<int> & layoutSize,
		const unsigned int calcFormat,
		sgeSize<int> & textSize);
private:
	void * mD3DXFont;
};

class sgeSound : public sgeNonCopyable
{
public:
	sgeSound();
	virtual ~sgeSound();
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

class sgeFile : public sgeNonCopyable
{
public:
	sgeFile();
	virtual ~sgeFile();
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

class sgeModule : public sgeNonCopyable
{
public:
	sgeModule();
	sgeModule(const wchar_t * moduleFileName);
	virtual ~sgeModule();
public:
	bool createW(const wchar_t * moduleFileName);
	void destroy(void);
	void * getProcAddressW(const wchar_t * procName);
	void * getProcAddressA(const char * procName);
private:
	void * mModuleHandle;
};

class sgeEngine : public sgeNonCopyable
{
public:
	static sgeEngine * get(void);
public:
	sgeEngine();
	virtual ~sgeEngine();
public:
	void go(
		const wchar_t * windowTitle,
		const int screenWidth,
		const int screenHeight);
public:
	void pushGameState(sgeGameState * gameState);
	void popGameState(void);
	void popAllGameState(void);
	sgeGameState * getRunningGameState(void);
public:
	bool paintPoint(
		const sgePoint<float> & pos,
		const unsigned int color);
	bool paintLine(
		const sgePoint<float> & posStart,
		const sgePoint<float> & posEnd,
		const unsigned int color);
	bool paintTriangle(
		const sgePoint<float> & pt1,
		const sgePoint<float> & pt2,
		const sgePoint<float> & pt3,
		const unsigned int color,
		const bool solid);
	bool paintRectangle(
		const sgePoint<float> & pos,
		const sgeSize<float> & size,
		const unsigned int color,
		const bool solid);
public:
	bool isKeyDown(const int keyCode) const;
public:
	virtual bool onCreate(void);
	virtual void onDestroy(void);
private:
	unsigned char mKeysStateArray[256];
	sgeList<sgeGameState *> mGameStateList;
};

class sgeStringTool
{
public:
	static bool a2w(const char * stringA, sgeStringW & stringW);
	static bool w2a(const wchar_t * stringW, sgeStringA & stringA);
	static int findA(const char * string, const char * subString);
	static int findW(const wchar_t * string, const wchar_t * subString);
};

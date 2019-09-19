
#pragma once

#include "glNonCopyable.h"
#include "glList.h"
#include "glPoint.h"
#include "glSize.h"

class glGameState;

//
// @brief 引擎类
//
class glEngine : public glNonCopyable {
public:
	//
	// @brief 获取引擎实例指针
	//
	static glEngine * get(void);
public:
	glEngine();
	virtual ~glEngine();
public:
	//
	// @brief 运行引擎
	//
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

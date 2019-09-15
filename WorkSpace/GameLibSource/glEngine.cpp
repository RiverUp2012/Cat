
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

typedef BOOL(WINAPI * sgeGetKeyboardState)(
	PBYTE lpKeyState);
typedef BOOL(WINAPI * sgePeekMessageW)(
	LPMSG lpMsg,
	HWND hWnd,
	UINT wMsgFilterMin,
	UINT wMsgFilterMax,
	UINT wRemoveMsg);
typedef BOOL(WINAPI * sgeTranslateMessage)(
	CONST MSG *lpMsg);
typedef LRESULT(WINAPI * sgeDispatchMessageW)(
	CONST MSG *lpMsg);

static glEngine * gEngine = 0;
static sgeGetKeyboardState gGetKeyboardState = 0;
static sgePeekMessageW gPeekMessageW = 0;
static sgeTranslateMessage gTranslateMessage = 0;
static sgeDispatchMessageW gDispatchMessageW = 0;

glEngine * glEngine::get(void)
{
	return gEngine;
}

glEngine::glEngine()
{
	if (gModuleUser32.createW(L"user32.dll"))
	{
		gGetKeyboardState = (sgeGetKeyboardState)
			gModuleUser32.getProcAddressA("GetKeyboardState");
		gPeekMessageW = (sgePeekMessageW)
			gModuleUser32.getProcAddressA("PeekMessageW");
		gTranslateMessage = (sgeTranslateMessage)
			gModuleUser32.getProcAddressA("TranslateMessage");
		gDispatchMessageW = (sgeDispatchMessageW)
			gModuleUser32.getProcAddressA("DispatchMessageW");
	}

	memset(&mKeysStateArray, 0, sizeof(mKeysStateArray));

	gEngine = this;
}

glEngine::~glEngine()
{
	gEngine = 0;
}

void glEngine::go(
	const wchar_t * windowTitle,
	const int screenWidth,
	const int screenHeight)
{
	MSG msg = { 0 };
	wchar_t moduleFileName[520] = { 0 };
	glPerformanceCounter pcFrameElapse;
	float frameElapse = 0;

	gModuleD3D9.createW(L"d3d9.dll");
	gModuleDSound.createW(L"dsound.dll");

	for (int i = 80; i >= 30; --i)
	{
		swprintf_s(moduleFileName, L"d3dx9_%d.dll", i);
		if (gModuleD3DX9.createW(moduleFileName))
		{
			break;
		}
	}

	if (gWindow.createW(windowTitle, screenWidth, screenHeight) &&
		gVideoDevice.create(gWindow, screenWidth, screenHeight) &&
		gSoundDevice.create(gWindow))
	{
		if (onCreate())
		{
			while (gWindow.isAlready())
			{
				if (gPeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
				{
					if (WM_QUIT == msg.message)
					{
						break;
					}

					gTranslateMessage(&msg);
					gDispatchMessageW(&msg);
				}
				else
				{
					frameElapse = pcFrameElapse.getElapseF32();
					if (frameElapse <= 0.0f || frameElapse > 0.1f)
					{
						frameElapse = 0.0333333334f;
					}

					if (!gGetKeyboardState(mKeysStateArray))
					{
						break;
					}

					glGameState * gameState = getRunningGameState();
					if (gameState)
					{
						gameState->onUpdate(frameElapse);
					}

					if (!gVideoDevice.clear(0xff000000))
					{
						break;
					}

					gameState = getRunningGameState();
					if (gameState)
					{
						gameState->onPaint();
					}
					
					if (!gVideoDevice.present())
					{
						break;
					}

					pcFrameElapse.tick();
				}
			}
		}

		popAllGameState();
		onDestroy();

		gSoundDevice.destroy();
		gVideoDevice.destroy();
		gWindow.destroy();
	}
}

void glEngine::pushGameState(glGameState * gameState)
{
	if (gameState)
	{
		if (mGameStateList.getNodeCount() > 0)
		{
			glList<glGameState *>::glIterator iter = mGameStateList.begin();
			if (iter.isValid())
			{
				glGameState * gameState = iter.getData();
				if (gameState)
				{
					gameState->onLeave();
				}
			}
		}

		gameState->addRef();
		gameState->onCreate();
		gameState->onEnter();

		mGameStateList.pushBack(gameState);
	}
}

void glEngine::popGameState(void)
{
	if (mGameStateList.getNodeCount() > 0)
	{
		glList<glGameState *>::glIterator iter = mGameStateList.begin();
		if (iter.isValid())
		{
			glGameState * gameState = iter.getData();
			if (gameState)
			{
				gameState->onLeave();
				gameState->onDestroy();
				gameState->release();
				gameState = 0;
			}
		}
		mGameStateList.popFront();

		if (mGameStateList.getNodeCount() > 0)
		{
			iter = mGameStateList.begin();
			if (iter.isValid())
			{
				glGameState * gameState = iter.getData();
				if (gameState)
				{
					gameState->onEnter();
				}
			}
		}
	}
}

void glEngine::popAllGameState(void)
{
	while (mGameStateList.getNodeCount() > 0)
	{
		glList<glGameState *>::glIterator iter = mGameStateList.begin();
		if (iter.isValid())
		{
			glGameState * gameState = iter.getData();
			if (gameState)
			{
				gameState->onLeave();
				gameState->onDestroy();
				gameState->release();
				gameState = 0;
			}
		}

		mGameStateList.popFront();
	}
}

glGameState * glEngine::getRunningGameState(void)
{
	if (mGameStateList.getNodeCount() > 0)
	{
		glList<glGameState *>::glIterator iter = mGameStateList.begin();
		if (iter.isValid())
		{
			return iter.getData();
		}
	}

	return 0;
}

bool glEngine::paintPoint(
	const glPoint<float> & pos,
	const unsigned int color)
{
	gBatchSprite.flush();

	return gBatchPrimitive.paintPoint(pos, color);
}

bool glEngine::paintLine(
	const glPoint<float> & posStart,
	const glPoint<float> & posEnd,
	const unsigned int color)
{
	gBatchSprite.flush();

	return gBatchPrimitive.paintLine(posStart, posEnd, color);
}

bool glEngine::paintTriangle(
	const glPoint<float> & pt1,
	const glPoint<float> & pt2,
	const glPoint<float> & pt3,
	const unsigned int color,
	const bool solid)
{
	gBatchSprite.flush();

	return gBatchPrimitive.paintTriangle(pt1, pt2, pt3, color, solid);
}

bool glEngine::paintRectangle(
	const glPoint<float> & pos,
	const glSize<float> & size,
	const unsigned int color,
	const bool solid)
{
	gBatchSprite.flush();

	return gBatchPrimitive.paintRectangle(pos, size, color, solid);
}

bool glEngine::isKeyDown(const int keyCode) const
{
	assert(keyCode >= 0 && keyCode <= _countof(mKeysStateArray));

	return mKeysStateArray[keyCode] & 0x80 ? true : false;
}

bool glEngine::onCreate(void)
{
	return true;
}

void glEngine::onDestroy(void)
{

}

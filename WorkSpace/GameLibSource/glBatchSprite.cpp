
#include "../GameLib.h"
#include "../Include/GameLibPrivate.h"

#define SGE_SPRITE_VERTEX_SIZE (sizeof(glSpriteVertex))
#define SGE_SPRITE_VERTEX_FVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SGE_MAX_SPRITE_VERTEX (1024 * 8)

glBatchSprite::glBatchSprite()
{
	mVertexList = 0;
	mD3DTex9 = 0;
	mSpriteCount = 0;
}

glBatchSprite::~glBatchSprite()
{
	destroy();
}

bool glBatchSprite::create(void)
{
	destroy();

	if (mVertexBuffer.create(
		SGE_SPRITE_VERTEX_SIZE * SGE_MAX_SPRITE_VERTEX,
		SGE_SPRITE_VERTEX_FVF))
	{
		lockVertexBuffer();

		return true;
	}

	return false;
}

void glBatchSprite::destroy(void)
{
	unlockVertexBuffer();

	if (mD3DTex9)
	{
		if (gVideoDevice.isAlready())
		{
			mD3DTex9->Release();
		}
	}

	mVertexBuffer.destroy();
	mD3DTex9 = 0;
	mVertexList = 0;
	mSpriteCount = 0;
}

bool glBatchSprite::flush(void)
{
	bool ret = false;

	IDirect3DDevice9 * d3dDev9 = gVideoDevice.getIDirect3DDevice9();
	if (mVertexBuffer.isAlready() && d3dDev9)
	{
		if (mD3DTex9 && mSpriteCount > 0)
		{
			unlockVertexBuffer();

			if (SUCCEEDED(d3dDev9->SetTexture(
				0,
				mD3DTex9)))
			{
				if (SUCCEEDED(d3dDev9->SetStreamSource(
					0,
					mVertexBuffer.getIDirect3DVertexBuffer9(),
					0,
					SGE_SPRITE_VERTEX_SIZE)))
				{
					if (SUCCEEDED(d3dDev9->SetFVF(SGE_SPRITE_VERTEX_FVF)))
					{
						if (SUCCEEDED(d3dDev9->DrawPrimitive(
							D3DPT_TRIANGLELIST,
							0,
							mSpriteCount * 2)))
						{
							mSpriteCount = 0;

							ret = true;
						}
					}
				}
			}
		}
		else
		{
			ret = true;
		}
	}

	return ret;
}

bool glBatchSprite::paintSprite(IDirect3DTexture9 * d3dTex9, glSpriteVertex * vertexList)
{
	if (d3dTex9 && vertexList && mVertexBuffer.isAlready())
	{
		if (d3dTex9 != mD3DTex9)
		{
			flush();

			if (mD3DTex9)
			{
				if (gVideoDevice.isAlready())
				{
					mD3DTex9->Release();
				}
			}

			mD3DTex9 = d3dTex9;
			mD3DTex9->AddRef();
		}

		if (mSpriteCount * 6 >= SGE_MAX_SPRITE_VERTEX)
		{
			flush();

			mSpriteCount = 0;
		}

		lockVertexBuffer();
		if (mVertexList)
		{
			glSpriteVertex * vertexListTemp = &mVertexList[mSpriteCount * 6];
			++mSpriteCount;

			vertexListTemp[0] = vertexList[0];
			vertexListTemp[1] = vertexList[1];
			vertexListTemp[2] = vertexList[2];

			vertexListTemp[3] = vertexList[1];
			vertexListTemp[4] = vertexList[3];
			vertexListTemp[5] = vertexList[2];

			return true;
		}
	}

	return false;
}

void glBatchSprite::lockVertexBuffer(void)
{
	if (mVertexBuffer.isAlready() && !mVertexList)
	{
		mVertexList = (glSpriteVertex *)mVertexBuffer.lock();
	}
}

void glBatchSprite::unlockVertexBuffer(void)
{
	if (mVertexBuffer.isAlready() && mVertexList)
	{
		if (mVertexBuffer.unlock())
		{
			mVertexList = 0;
		}
	}
}

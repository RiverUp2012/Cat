
#include "../SurgeGameEngine.h"
#include "../Include/SurgeGameEnginePrivate.h"

#define SGE_PRIMITIVE_VERTEX_SIZE (sizeof(sgePrimitiveVertex))
#define SGE_PRIMITIVE_VERTEX_FVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define SGE_MAX_PRIMITIVE_VERTEX (1024 * 8)

sgeBatchPrimitive::sgeBatchPrimitive()
{
	mVertexList = 0;
	mPrimitiveCount = 0;
	mPrimitiveType = sgePrimitiveTypeUnknown;
}

sgeBatchPrimitive::~sgeBatchPrimitive()
{
	destroy();
}

bool sgeBatchPrimitive::create(void)
{
	destroy();

	if (mVertexBuffer.create(
		SGE_PRIMITIVE_VERTEX_SIZE * SGE_MAX_PRIMITIVE_VERTEX,
		SGE_PRIMITIVE_VERTEX_FVF))
	{
		lockVertexBuffer();

		return true;
	}

	return false;
}

void sgeBatchPrimitive::destroy(void)
{
	unlockVertexBuffer();

	mVertexBuffer.destroy();
	mVertexList = 0;
	mPrimitiveCount = 0;
	mPrimitiveType = sgePrimitiveTypeUnknown;
}

bool sgeBatchPrimitive::flush(void)
{
	bool ret = false;
	D3DPRIMITIVETYPE d3dPrimType = D3DPT_POINTLIST;

	IDirect3DDevice9 * d3dDev9 = gVideoDevice.getIDirect3DDevice9();
	if (mVertexBuffer.isAlready() && d3dDev9)
	{
		if (sgePrimitiveTypeUnknown != mPrimitiveType && mPrimitiveCount > 0)
		{
			unlockVertexBuffer();

			if (sgePrimitiveTypePoint == mPrimitiveType)
			{
				d3dPrimType = D3DPT_POINTLIST;
			}
			else if (sgePrimitiveTypeLine == mPrimitiveType)
			{
				d3dPrimType = D3DPT_LINELIST;
			}
			else if (sgePrimitiveTypeTriangle == mPrimitiveType)
			{
				d3dPrimType = D3DPT_TRIANGLELIST;
			}

			if (SUCCEEDED(d3dDev9->SetTexture(
				0,
				0)))
			{
				if (SUCCEEDED(d3dDev9->SetStreamSource(
					0,
					mVertexBuffer.getIDirect3DVertexBuffer9(),
					0,
					SGE_PRIMITIVE_VERTEX_SIZE)))
				{
					if (SUCCEEDED(d3dDev9->SetFVF(SGE_PRIMITIVE_VERTEX_FVF)))
					{
						if (SUCCEEDED(d3dDev9->DrawPrimitive(
							d3dPrimType,
							0,
							mPrimitiveCount)))
						{
							mPrimitiveCount = 0;

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

bool sgeBatchPrimitive::paintPoint(
	const sgePoint<float> & pos,
	const unsigned int color)
{
	if (mVertexBuffer.isAlready())
	{
		if (sgePrimitiveTypePoint != mPrimitiveType ||
			mPrimitiveCount >= SGE_MAX_PRIMITIVE_VERTEX)
		{
			flush();

			mPrimitiveType = sgePrimitiveTypePoint;
			mPrimitiveCount = 0;
		}

		lockVertexBuffer();
		if (mVertexList)
		{
			sgePrimitiveVertex * vertexList = &mVertexList[mPrimitiveCount];
			++mPrimitiveCount;

			vertexList[0].x = pos.mX;
			vertexList[0].y = pos.mY;
			vertexList[0].diffuse = color;

			return true;
		}
	}

	return false;
}

bool sgeBatchPrimitive::paintLine(
	const sgePoint<float> & posStart,
	const sgePoint<float> & posEnd,
	const unsigned int color)
{
	if (mVertexBuffer.isAlready())
	{
		if (sgePrimitiveTypeLine != mPrimitiveType ||
			mPrimitiveCount * 2 >= SGE_MAX_PRIMITIVE_VERTEX)
		{
			flush();

			mPrimitiveType = sgePrimitiveTypeLine;
			mPrimitiveCount = 0;
		}

		lockVertexBuffer();
		if (mVertexList)
		{
			sgePrimitiveVertex * vertexList = &mVertexList[mPrimitiveCount * 2];
			++mPrimitiveCount;

			vertexList[0].x = posStart.mX;
			vertexList[0].y = posStart.mY;
			vertexList[0].diffuse = color;

			vertexList[1].x = posEnd.mX;
			vertexList[1].y = posEnd.mY;
			vertexList[1].diffuse = color;

			return true;
		}
	}

	return false;
}

bool sgeBatchPrimitive::paintTriangle(
	const sgePoint<float> & pt1,
	const sgePoint<float> & pt2,
	const sgePoint<float> & pt3,
	const unsigned int color,
	const bool solid)
{
	if (solid)
	{
		if (mVertexBuffer.isAlready())
		{
			if (sgePrimitiveTypeTriangle != mPrimitiveType ||
				mPrimitiveCount * 3 >= SGE_MAX_PRIMITIVE_VERTEX)
			{
				flush();

				mPrimitiveType = sgePrimitiveTypeTriangle;
				mPrimitiveCount = 0;
			}

			lockVertexBuffer();
			if (mVertexList)
			{
				sgePrimitiveVertex * vertexList = &mVertexList[mPrimitiveCount * 3];
				++mPrimitiveCount;

				vertexList[0].x = pt1.mX;
				vertexList[0].y = pt1.mY;
				vertexList[0].diffuse = color;

				vertexList[1].x = pt2.mX;
				vertexList[1].y = pt2.mY;
				vertexList[1].diffuse = color;

				vertexList[2].x = pt3.mX;
				vertexList[2].y = pt3.mY;
				vertexList[2].diffuse = color;

				return true;
			}
		}
	}
	else
	{
		if (paintLine(pt1, pt2, color) &&
			paintLine(pt2, pt3, color) &&
			paintLine(pt3, pt1, color))
		{
			return true;
		}
	}

	return false;
}

bool sgeBatchPrimitive::paintRectangle(
	const sgePoint<float> & pos,
	const sgeSize<float> & size,
	const unsigned int color,
	const bool solid)
{
	const sgePoint<float> & pt1 = pos;
	const sgePoint<float> & pt2 = sgePoint<float>(pos.mX + size.mWidth, pos.mY);
	const sgePoint<float> & pt3 = sgePoint<float>(pos.mX, pos.mY + size.mHeight);
	const sgePoint<float> & pt4 = sgePoint<float>(pos.mX + size.mWidth, pos.mY + size.mHeight);

	if (solid)
	{
		if (paintTriangle(pt1, pt2, pt3, color, solid) &&
			paintTriangle(pt2, pt4, pt3, color, solid))
		{
			return true;
		}
	}
	else
	{
		if (paintLine(pt1, pt2, color) &&
			paintLine(pt2, pt4, color) &&
			paintLine(pt4, pt3, color) &&
			paintLine(pt3, pt1, color))
		{
			return true;
		}
	}

	return false;
}

void sgeBatchPrimitive::lockVertexBuffer(void)
{
	if (mVertexBuffer.isAlready() && !mVertexList)
	{
		mVertexList = (sgePrimitiveVertex *)mVertexBuffer.lock();
		if (mVertexList)
		{
			if (1.0f != mVertexList[0].rhw)
			{
				for (int i = 0; i < SGE_MAX_PRIMITIVE_VERTEX; ++i)
				{
					mVertexList[i].rhw = 1.0f;
					mVertexList[i].z = 0.0f;
				}
			}
		}
	}
}

void sgeBatchPrimitive::unlockVertexBuffer(void)
{
	if (mVertexBuffer.isAlready() && mVertexList)
	{
		if (mVertexBuffer.unlock())
		{
			mVertexList = 0;
		}
	}
}

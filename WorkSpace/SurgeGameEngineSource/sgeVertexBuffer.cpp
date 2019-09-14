
#include "../SurgeGameEngine.h"
#include "../Include/SurgeGameEnginePrivate.h"

sgeVertexBuffer::sgeVertexBuffer()
{
	mD3DVB9 = 0;
}

sgeVertexBuffer::~sgeVertexBuffer()
{
	destroy();
}

bool sgeVertexBuffer::create(const int size, const int fvf)
{
	destroy();

	IDirect3DDevice9 * d3dDev9 = gVideoDevice.getIDirect3DDevice9();
	if (d3dDev9 && size > 0 && fvf > 0)
	{
		if (SUCCEEDED(d3dDev9->CreateVertexBuffer(
			size,
			0,
			fvf,
			D3DPOOL_DEFAULT,
			&mD3DVB9,
			0)))
		{
			return true;
		}
	}

	return false;
}

void sgeVertexBuffer::destroy(void)
{
	if (mD3DVB9)
	{
		if (gVideoDevice.isAlready())
		{
			mD3DVB9->Release();
		}
	}

	mD3DVB9 = 0;
}

bool sgeVertexBuffer::isAlready(void) const
{
	return mD3DVB9 ? true : false;
}

void * sgeVertexBuffer::lock(const int offset, const int size)
{
	void * vertexBuffer = 0;

	if (mD3DVB9)
	{
		mD3DVB9->Lock(offset, size, &vertexBuffer, 0);
	}

	return vertexBuffer;
}

bool sgeVertexBuffer::unlock(void)
{
	if (mD3DVB9)
	{
		if (SUCCEEDED(mD3DVB9->Unlock()))
		{
			return true;
		}
	}

	return false;
}

IDirect3DVertexBuffer9 * sgeVertexBuffer::getIDirect3DVertexBuffer9(void) const
{
	return mD3DVB9;
}

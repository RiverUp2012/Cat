
#include "../Include/Private.h"
#include "../Include/D3D9Common.h"
#include "../Include/CompileConfig.h"

#if defined T_USE_D3D9

typedef IDirect3D9 * (WINAPI * TDirect3DCreate9)(
	UINT SDKVersion);

#define T_MAX_D3D9PAINTDEVICE (32)

typedef struct _T_D3D9PAINTDEVICE
{
	struct IDirect3DDevice9 * mD3DDev9;
	D3DPRESENT_PARAMETERS mD3DPP;
	HWND mWndHandle;
	T_OBJECT mBatchGraph;
}
T_D3D9PAINTDEVICE;

static T_D3D9PAINTDEVICE gD3D9PaintDeviceArray[T_MAX_D3D9PAINTDEVICE] = { 0 };
static T_OBJECT gModuleD3D9 = 0;
static TDirect3DCreate9 gDirect3DCreate9 = 0;

static T_D3D9PAINTDEVICE * TFindUnuseD3D9PaintDevice(void)
{
	for (int i = 0; i < T_MAX_D3D9PAINTDEVICE; ++i)
	{
		if (!gD3D9PaintDeviceArray[i].mD3DDev9)
		{
			return &gD3D9PaintDeviceArray[i];
		}
	}

	return 0;
}

static T_D3D9PAINTDEVICE * TFindD3D9PaintDeviceByHWND(
	const HWND wndHandle)
{
	for (int i = 0; i < T_MAX_D3D9PAINTDEVICE; ++i)
	{
		if (wndHandle == gD3D9PaintDeviceArray[i].mWndHandle)
		{
			return &gD3D9PaintDeviceArray[i];
		}
	}

	return 0;
}

static void TSetupDefaultRenderStatus(
	struct IDirect3DDevice9 * d3dDev9)
{
	if (d3dDev9)
	{
		d3dDev9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		d3dDev9->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		d3dDev9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		d3dDev9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		d3dDev9->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		d3dDev9->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		d3dDev9->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);

		d3dDev9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		d3dDev9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
		d3dDev9->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

		d3dDev9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		d3dDev9->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		d3dDev9->SetRenderState(D3DRS_ALPHAREF, 0x00);
	}
}

#endif

T_OBJECT TD3D9PaintDeviceCreate(
	T_OBJECT window,
	const int bufferWidth,
	const int bufferHeight,
	const int fullscreen,
	const int vsync)
{
#if defined T_USE_D3D9

	HWND wndHandle = TWindowGetHandle(window);
	T_D3D9PAINTDEVICE * d3d9PaintDeviceImpl = TFindUnuseD3D9PaintDevice();
	struct IDirect3D9 * d3d9 = 0;
	HRESULT comRet = S_OK;
	T_OBJECT d3d9PaintDevice = 0;

	if (!gModuleD3D9)
	{
		gModuleD3D9 = TModuleLoadW(L"d3d9.dll");
		if (gModuleD3D9)
		{
			gDirect3DCreate9 = (TDirect3DCreate9)TModuleGetProcAddress(
				gModuleD3D9,
				L"Direct3DCreate9");
		}
	}

	if (IsWindow(wndHandle) && 
		!TFindD3D9PaintDeviceByHWND(wndHandle) &&
		d3d9PaintDeviceImpl &&
		gDirect3DCreate9)
	{
		d3d9 = gDirect3DCreate9(D3D_SDK_VERSION);
		if (d3d9)
		{
			d3d9PaintDeviceImpl->mD3DPP.BackBufferCount = 1;
			d3d9PaintDeviceImpl->mD3DPP.BackBufferFormat = D3DFMT_X8R8G8B8;
			d3d9PaintDeviceImpl->mD3DPP.BackBufferWidth = bufferWidth;
			d3d9PaintDeviceImpl->mD3DPP.BackBufferHeight = bufferHeight;
			d3d9PaintDeviceImpl->mD3DPP.hDeviceWindow = wndHandle;
			d3d9PaintDeviceImpl->mD3DPP.PresentationInterval =
				vsync ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
			d3d9PaintDeviceImpl->mD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
			d3d9PaintDeviceImpl->mD3DPP.Windowed = fullscreen ? FALSE : TRUE;

			comRet = d3d9->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				wndHandle,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3d9PaintDeviceImpl->mD3DPP,
				&d3d9PaintDeviceImpl->mD3DDev9);
			if (FAILED(comRet))
			{
				comRet = d3d9->CreateDevice(
					D3DADAPTER_DEFAULT,
					D3DDEVTYPE_HAL,
					wndHandle,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3d9PaintDeviceImpl->mD3DPP,
					&d3d9PaintDeviceImpl->mD3DDev9);
			}

			if (SUCCEEDED(comRet))
			{
				TSetupDefaultRenderStatus(d3d9PaintDeviceImpl->mD3DDev9);

				d3d9PaintDeviceImpl->mWndHandle = wndHandle;
				d3d9PaintDeviceImpl->mBatchGraph = TD3D9BatchGraphCreate(
					(T_OBJECT)d3d9PaintDeviceImpl);

				d3d9PaintDevice = (T_OBJECT)d3d9PaintDeviceImpl;
			}

			d3d9->Release();
			d3d9 = 0;
		}

		return d3d9PaintDevice;
	}

#endif

	return 0;
}

void TD3D9PaintDeviceDestroy(
	T_OBJECT d3d9PaintDevice)
{
#if defined T_USE_D3D9

	T_D3D9PAINTDEVICE * d3d9PaintDeviceImpl = (T_D3D9PAINTDEVICE *)d3d9PaintDevice;
	if (d3d9PaintDeviceImpl)
	{
		if (d3d9PaintDeviceImpl->mBatchGraph)
		{
			TD3D9BatchGraphDestroy(d3d9PaintDeviceImpl->mBatchGraph);
			d3d9PaintDeviceImpl->mBatchGraph = 0;
		}

		if (d3d9PaintDeviceImpl->mD3DDev9)
		{
			d3d9PaintDeviceImpl->mD3DDev9->Release();
			d3d9PaintDeviceImpl->mD3DDev9 = 0;
		}

		TMemset(d3d9PaintDeviceImpl, sizeof(T_D3D9PAINTDEVICE), 0);
	}

#endif
}

int TD3D9PaintDeviceClear(
	T_OBJECT d3d9PaintDevice,
	const unsigned int clearColor)
{
#if defined T_USE_D3D9

	T_D3D9PAINTDEVICE * d3d9PaintDeviceImpl = (T_D3D9PAINTDEVICE *)d3d9PaintDevice;
	if (d3d9PaintDeviceImpl && d3d9PaintDeviceImpl->mD3DDev9)
	{
		if (SUCCEEDED(d3d9PaintDeviceImpl->mD3DDev9->Clear(
			0,
			0,
			D3DCLEAR_TARGET,
			clearColor,
			0,
			0)))
		{
			if (SUCCEEDED(d3d9PaintDeviceImpl->mD3DDev9->BeginScene()))
			{
				return T_TRUE;
			}
		}
	}

#endif

	return T_FALSE;
}

int TD3D9PaintDevicePresent(
	T_OBJECT d3d9PaintDevice)
{
#if defined T_USE_D3D9

	T_D3D9PAINTDEVICE * d3d9PaintDeviceImpl = (T_D3D9PAINTDEVICE *)d3d9PaintDevice;
	if (d3d9PaintDeviceImpl && d3d9PaintDeviceImpl->mD3DDev9)
	{
		if (d3d9PaintDeviceImpl->mBatchGraph)
		{
			TD3D9BatchGraphFlush(
				d3d9PaintDeviceImpl->mBatchGraph,
				d3d9PaintDevice);
		}

		if (SUCCEEDED(d3d9PaintDeviceImpl->mD3DDev9->EndScene()))
		{
			if (SUCCEEDED(d3d9PaintDeviceImpl->mD3DDev9->Present(
				0,
				0,
				0,
				0)))
			{
				return T_TRUE;
			}
		}
	}

#endif

	return T_FALSE;
}

#if defined T_USE_D3D9

struct IDirect3DDevice9 * TD3D9PaintDeviceGetIDirect3DDevice9(
	T_OBJECT d3d9PaintDevice)
{
	T_D3D9PAINTDEVICE * d3d9PaintDeviceImpl = (T_D3D9PAINTDEVICE *)d3d9PaintDevice;

	return d3d9PaintDeviceImpl ? d3d9PaintDeviceImpl->mD3DDev9 : 0;
}

void TD3D9PaintDevicePaintGraph(
	T_OBJECT d3d9PaintDevice,
	T_D3D9VERTEXGRAPH * vertexList,
	T_OBJECT d3d9Texture)
{
	T_D3D9PAINTDEVICE * d3d9PaintDeviceImpl = (T_D3D9PAINTDEVICE *)d3d9PaintDevice;
	if (d3d9PaintDeviceImpl &&
		d3d9PaintDeviceImpl->mBatchGraph &&
		vertexList &&
		d3d9Texture)
	{
		TD3D9BatchGraphPaintGraph(
			d3d9PaintDeviceImpl->mBatchGraph,
			d3d9PaintDevice,
			vertexList,
			d3d9Texture);
	}
}

void TD3D9PaintDeviceFlushBatchGraph(
	T_OBJECT d3d9PaintDevice)
{
	T_D3D9PAINTDEVICE * d3d9PaintDeviceImpl = (T_D3D9PAINTDEVICE *)d3d9PaintDevice;
	if (d3d9PaintDeviceImpl &&
		d3d9PaintDeviceImpl->mBatchGraph)
	{
		TD3D9BatchGraphFlush(
			d3d9PaintDeviceImpl->mBatchGraph,
			d3d9PaintDevice);
	}
}

#endif // T_USE_D3D9

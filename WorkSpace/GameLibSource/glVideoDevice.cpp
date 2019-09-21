
#include "../GameLibInclude/glVideoDevice.h"
#include "../GameLibInclude/glWindow.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glGlobalData.h"

typedef IDirect3D9 * (WINAPI * glDirect3DCreate9)(
	UINT SDKVersion);

glVideoDevice::glVideoDevice() {
	mD3DDev9 = 0;
}

glVideoDevice::~glVideoDevice() {
	destroy();
}

bool glVideoDevice::create(
	glWindow & window,
	const int screenWidth,
	const int screenHeight) {
	bool ret = false;
	glDirect3DCreate9 direct3DCreate9 = 0;
	IDirect3D9 * d3d9 = 0;
	D3DPRESENT_PARAMETERS d3dpp = { 0 };
	if (!direct3DCreate9) {
		direct3DCreate9 = (glDirect3DCreate9)gModule_D3D9.getProcAddressA("Direct3DCreate9");
	}
	if (!mD3DDev9 && window.isAlready() && direct3DCreate9) {
		d3d9 = direct3DCreate9(D3D_SDK_VERSION);
		if (d3d9) {
			d3dpp.BackBufferCount = 1;
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
			d3dpp.BackBufferWidth = screenWidth;
			d3dpp.BackBufferHeight = screenHeight;
			d3dpp.hDeviceWindow = (HWND)window.getHandle();
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
			d3dpp.Windowed = TRUE;
			if (SUCCEEDED(d3d9->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				d3dpp.hDeviceWindow,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp,
				&mD3DDev9))) {
				setupDefaultRenderStatus();
				gBatchSprite.create();
				gBatchPrimitive.create();
				ret = true;
			}
			d3d9->Release();
			d3d9 = 0;
		}
	}
	return ret;
}

void glVideoDevice::destroy(void) {
	if (mD3DDev9) {
		mD3DDev9->Release();
		mD3DDev9 = 0;
	}
	gBatchSprite.destroy();
	gBatchPrimitive.destroy();
}

bool glVideoDevice::isAlready(void) const {
	return mD3DDev9 ? true : false;
}

IDirect3DDevice9 * glVideoDevice::getIDirect3DDevice9(void) const {
	return mD3DDev9;
}

bool glVideoDevice::clear(const unsigned int clearColor) {
	if (mD3DDev9) {
		if (SUCCEEDED(mD3DDev9->Clear(0, 0, D3DCLEAR_TARGET, clearColor, 0, 0))) {
			if (SUCCEEDED(mD3DDev9->BeginScene())) {
				return true;
			}
		}
	}
	return false;
}

bool glVideoDevice::present(void) {
	if (mD3DDev9) {
		gBatchSprite.flush();
		gBatchPrimitive.flush();
		if (SUCCEEDED(mD3DDev9->EndScene())) {
			if (SUCCEEDED(mD3DDev9->Present(0, 0, 0, 0))) {
				return true;
			}
		}
	}
	return false;
}

void glVideoDevice::setupDefaultRenderStatus(void) {
	if (mD3DDev9) {
		mD3DDev9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		mD3DDev9->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		mD3DDev9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		mD3DDev9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		mD3DDev9->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		mD3DDev9->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		mD3DDev9->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
		mD3DDev9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		mD3DDev9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
		mD3DDev9->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
		mD3DDev9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		mD3DDev9->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		mD3DDev9->SetRenderState(D3DRS_ALPHAREF, 0x00);
	}
}

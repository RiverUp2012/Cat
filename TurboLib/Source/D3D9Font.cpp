
#include "../Include/Private.h"
#include "../Include/D3D9Common.h"
#include "../Include/CompileConfig.h"

#if defined T_USE_D3D9

typedef HRESULT (WINAPI * TD3DXCreateFontW)(
	LPDIRECT3DDEVICE9       pDevice,
	INT                     Height,
	UINT                    Width,
	UINT                    Weight,
	UINT                    MipLevels,
	BOOL                    Italic,
	DWORD                   CharSet,
	DWORD                   OutputPrecision,
	DWORD                   Quality,
	DWORD                   PitchAndFamily,
	LPCWSTR                 pFaceName,
	LPD3DXFONT*             ppFont);

#define T_MAX_D3D9FONT (32)
#define T_MAX_D3D9FONT_FONT_NAME_SIZE (64)

typedef struct _T_D3D9FONT
{
	struct ID3DXFont * mD3DXFont;
	wchar_t mFontName[T_MAX_D3D9FONT_FONT_NAME_SIZE];
	int mFontWidth;
	int mFontHeight;
	int mRefCount;
	T_OBJECT mD3D9PaintDevice;
}
T_D3D9FONT;

static T_D3D9FONT gD3D9FontArray[T_MAX_D3D9FONT] = { 0 };
static TD3DXCreateFontW gD3DXCreateFontW = 0;

static T_D3D9FONT * TFindUnuseD3D9Font(void)
{
	for (int i = 0; i < T_MAX_D3D9FONT; ++i)
	{
		if (!gD3D9FontArray[i].mD3DXFont)
		{
			return &gD3D9FontArray[i];
		}
	}

	return 0;
}

static T_D3D9FONT * TFindD3D9FontByCreateParamW(
	const wchar_t * fontName,
	const int fontWidth,
	const int fontHeight)
{
	if (fontName)
	{
		for (int i = 0; i < T_MAX_D3D9FONT; ++i)
		{
			if (gD3D9FontArray[i].mD3DXFont &&
				0 == wcscmp(fontName, gD3D9FontArray[i].mFontName) &&
				fontWidth == gD3D9FontArray[i].mFontWidth &&
				fontHeight == gD3D9FontArray[i].mFontHeight)
			{
				return &gD3D9FontArray[i];
			}
		}
	}

	return 0;
}

#endif

T_OBJECT TD3D9FontCreateW(
	T_OBJECT d3d9PaintDevice,
	const wchar_t * fontName,
	const int fontWidth,
	const int fontHeight)
{
#if defined T_USE_D3D9

	T_D3D9FONT * d3d9FontImpl = 0;

	if (!gD3DXCreateFontW)
	{
		gD3DXCreateFontW = (TD3DXCreateFontW)TModuleGetProcAddress(
			TGetD3DX9Module(),
			L"D3DXCreateFontW");
	}

	if (fontName && gD3DXCreateFontW)
	{
		d3d9FontImpl = TFindD3D9FontByCreateParamW(fontName, fontWidth, fontHeight);
		if (d3d9FontImpl)
		{
			++d3d9FontImpl->mRefCount;

			return (T_OBJECT)d3d9FontImpl;
		}
		else
		{
			d3d9FontImpl = TFindUnuseD3D9Font();
			if (d3d9FontImpl)
			{
				d3d9FontImpl->mRefCount = 1;

				if (SUCCEEDED(gD3DXCreateFontW(
					TD3D9PaintDeviceGetIDirect3DDevice9(d3d9PaintDevice),
					fontHeight,
					fontWidth,
					400,
					1,
					FALSE,
					GB2312_CHARSET,
					0,
					0,
					0,
					fontName,
					&d3d9FontImpl->mD3DXFont)))
				{
					TStringCopyW(d3d9FontImpl->mFontName, fontName, 0);
					d3d9FontImpl->mFontWidth = fontWidth;
					d3d9FontImpl->mFontHeight = fontHeight;
					d3d9FontImpl->mD3D9PaintDevice = d3d9PaintDevice;

					return (T_OBJECT)d3d9FontImpl;
				}
			}
		}
	}

#endif // T_USE_D3D9

	return 0;
}

T_OBJECT TD3D9FontCreateA(
	T_OBJECT d3d9PaintDevice,
	const char * fontName,
	const int fontWidth,
	const int fontHeight)
{
	T_OBJECT d3d9Font = 0;
	wchar_t * fontNameW = 0;

	if (fontName)
	{
		fontNameW = TStringA2W(fontName);
		if (fontNameW)
		{
			d3d9Font = TD3D9FontCreateW(
				d3d9PaintDevice,
				fontNameW,
				fontWidth,
				fontHeight);

			TFree(fontNameW);
			fontNameW = 0;
		}
	}

	return d3d9Font;
}

void TD3D9FontDestroy(
	T_OBJECT d3d9Font)
{
#if defined T_USE_D3D9

	T_D3D9FONT * d3d9FontImpl = (T_D3D9FONT *)d3d9Font;
	if (d3d9FontImpl)
	{
		--d3d9FontImpl->mRefCount;
		if (d3d9FontImpl->mRefCount <= 0)
		{
			if (d3d9FontImpl->mD3DXFont)
			{
				d3d9FontImpl->mD3DXFont->Release();
				d3d9FontImpl->mD3DXFont = 0;
			}

			TMemset(d3d9FontImpl, sizeof(T_D3D9FONT), 0);
		}
	}

#endif // T_USE_D3D9
}

int TD3D9FontPaintTextW(
	T_OBJECT d3d9Font,
	const wchar_t * text,
	const int charsToPaint,
	const int x,
	const int y,
	const int width,
	const int height,
	const unsigned int format,
	const unsigned int color)
{
#if defined T_USE_D3D9

	RECT textRect = { 0 };

	T_D3D9FONT * d3d9FontImpl = (T_D3D9FONT *)d3d9Font;
	if (d3d9FontImpl && d3d9FontImpl->mD3DXFont && text)
	{
		TD3D9PaintDeviceFlushBatchGraph(d3d9FontImpl->mD3D9PaintDevice);

		textRect.left = x;
		textRect.top = y;
		textRect.right = x + width;
		textRect.bottom = y + height;

		if (SUCCEEDED(d3d9FontImpl->mD3DXFont->DrawTextW(
			0,
			text,
			charsToPaint,
			&textRect,
			format,
			color)))
		{
			return T_TRUE;
		}
	}

#endif // T_USE_D3D9

	return T_FALSE;
}

int TD3D9FontCalcTextSizeW(
	T_OBJECT d3d9Font,
	const wchar_t * text,
	const int charsToCalc,
	const int layoutWidth,
	const int layoutHeight,
	const unsigned int format,
	int * width,
	int * height)
{
#if defined T_USE_D3D9

	RECT textRect = { 0 };

	T_D3D9FONT * d3d9FontImpl = (T_D3D9FONT *)d3d9Font;
	if (d3d9FontImpl && d3d9FontImpl->mD3DXFont && text && (width || height))
	{
		textRect.right = layoutWidth;
		textRect.bottom = layoutHeight;

		if (SUCCEEDED(d3d9FontImpl->mD3DXFont->DrawTextW(
			0,
			text,
			charsToCalc,
			&textRect,
			format | DT_CALCRECT,
			0)))
		{
			if (width)
			{
				*width = textRect.right - textRect.left;
			}

			if (height)
			{
				*height = textRect.bottom - textRect.top;
			}

			return T_TRUE;
		}
	}

#endif // T_USE_D3D9

	return T_FALSE;
}

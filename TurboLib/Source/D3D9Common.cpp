
#include "../Include/D3D9Common.h"

#if defined T_USE_D3D9

static T_OBJECT gModuleD3DX = 0;

T_OBJECT TGetD3DX9Module(void)
{
	wchar_t moduleName[64] = { 0 };

	if (!gModuleD3DX)
	{
		for (int i = 80; i >= 30; --i)
		{
			swprintf_s(moduleName, 64, L"d3dx9_%d.dll", i);

			gModuleD3DX = TModuleLoadW(moduleName);
			if (gModuleD3DX)
			{
				break;
			}
		}
	}

	return gModuleD3DX;
}

#endif

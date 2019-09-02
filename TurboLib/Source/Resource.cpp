
#include "../TurboLib.h"
#include "../Include/Private.h"

int TResourceLoadW(
	T_OBJECT module,
	const wchar_t * resourceType,
	const int resourceId,
	T_RESOURCE * resource)
{
	HMODULE moduleHandle = module ? TModuleGetHandle(module) : GetModuleHandleW(0);
	HRSRC resInfoBlockHandle = 0;

	if (resourceType && resourceId && resource)
	{
		resInfoBlockHandle = FindResourceW(
			moduleHandle,
			MAKEINTRESOURCEW(resourceId),
			resourceType);
		if (resInfoBlockHandle)
		{
			resource->mSize = SizeofResource(moduleHandle, resInfoBlockHandle);
			resource->mData = LockResource(resInfoBlockHandle);

			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TResourceLoadA(
	T_OBJECT module,
	const char * resourceType,
	const int resourceId,
	T_RESOURCE * resource)
{
	HMODULE moduleHandle = module ? TModuleGetHandle(module) : GetModuleHandleW(0);
	HRSRC resInfoBlockHandle = 0;

	if (resourceType && resourceId && resource)
	{
		resInfoBlockHandle = FindResourceA(
			moduleHandle,
			MAKEINTRESOURCEA(resourceId),
			resourceType);
		if (resInfoBlockHandle)
		{
			resource->mSize = SizeofResource(moduleHandle, resInfoBlockHandle);
			resource->mData = LockResource(resInfoBlockHandle);

			return T_TRUE;
		}
	}

	return T_FALSE;
}

int TResourceExportToFileW(
	T_OBJECT module,
	const wchar_t * resourceType,
	const int resourceId,
	const wchar_t * fileName)
{
	int ret = T_FALSE;
	T_RESOURCE resource = { 0 };
	T_OBJECT file = 0;

	if (TResourceLoadW(module, resourceType, resourceId, &resource))
	{
		file = TFileOpenW(fileName, T_TRUE, T_FALSE);
		if (file)
		{
			if (TFileWrite(file, resource.mData, resource.mSize))
			{
				ret = T_TRUE;
			}

			TFileClose(file);
			file = 0;
		}
	}

	return ret;
}

int TResourceExportToFileA(
	T_OBJECT module,
	const char * resourceType,
	const int resourceId,
	const char * fileName)
{
	int ret = T_FALSE;
	T_RESOURCE resource = { 0 };
	T_OBJECT file = 0;

	if (TResourceLoadA(module, resourceType, resourceId, &resource))
	{
		file = TFileOpenA(fileName, T_TRUE, T_FALSE);
		if (file)
		{
			if (TFileWrite(file, resource.mData, resource.mSize))
			{
				ret = T_TRUE;
			}

			TFileClose(file);
			file = 0;
		}
	}

	return ret;
}

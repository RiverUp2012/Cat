
#include "../GameLibInclude/glDriveHelper.h"
#include "../GameLibInclude/glPrivate.h"

void glDriveHelper::getDriveNameListW(glArray<glStringW> & driveNameArray) {
	const DWORD drives = GetLogicalDrives();
	wchar_t driveName[4] = { 0 };
	if (driveNameArray.resize(sizeof(drives)* 8)) {
		driveName[1] = L':';
		driveName[2] = L'\\';
		driveName[3] = L'\0';
		for (unsigned int i = 0; i < sizeof(drives)* 8; ++i) {
			if (drives & (1 << i)) {
				driveName[0] = L'A' + i;
				driveNameArray.setAt(i, driveName);
			}
		}
	}
}

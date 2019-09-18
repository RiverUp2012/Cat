
#include "CompileConfig.h"

GL_TEST_CASE(TestDrive) {
	glArray<glStringW> driveNameArray;
	glDriveHelper::getDriveNameListW(driveNameArray);
	for (int i = 0; i < driveNameArray.getCapacity(); ++i) {
		if (driveNameArray.getAt(i).getLength()) {
			OutputDebugStringW(driveNameArray.getAt(i));
			OutputDebugStringW(L"\r\n");
		}
	}
}

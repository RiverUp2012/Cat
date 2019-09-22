
#include "../GameLibInclude/glConsole.h"
#include "../GameLibInclude/glPrivate.h"
#include "../GameLibInclude/glException.h"

bool glConsole::setTextColor(
	const bool red,
	const bool green,
	const bool blue,
	const bool intensity) {
	WORD textTttributes = 0;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE != consoleHandle) {
		if (red) textTttributes |= FOREGROUND_RED;
		if (green) textTttributes |= FOREGROUND_GREEN;
		if (blue) textTttributes |= FOREGROUND_BLUE;
		if (intensity) textTttributes |= FOREGROUND_INTENSITY;
		if (SetConsoleTextAttribute(consoleHandle, textTttributes)) {
			return true;
		}
		else {
			throw glWin32APIException(L"SetConsoleTextAttribute", GetLastError());
		}
	}
	return false;
}

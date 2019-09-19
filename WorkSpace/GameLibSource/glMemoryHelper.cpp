
#include "../GameLibInclude/glMemoryHelper.h"

void glMemoryHelper::xor(unsigned char * buffer, const int bytesToProcess) {
	if (buffer && bytesToProcess > 0) {
		for (int i = 0; i < bytesToProcess; ++i) {
			buffer[i] ^= buffer[i];
		}
	}
}

void glMemoryHelper::xor(unsigned char * buffer, const int bytesToProcess, const unsigned char factorChar) {
	if (buffer && bytesToProcess > 0) {
		for (int i = 0; i < bytesToProcess; ++i) {
			buffer[i] = buffer[i] ^ factorChar;
		}
	}
}

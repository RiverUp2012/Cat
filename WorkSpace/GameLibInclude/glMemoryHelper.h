
#pragma once

class glMemoryHelper {
public:
	static void xor(unsigned char * buffer, const int bytesToProcess);
	static void xor(unsigned char * buffer, const int bytesToProcess, const unsigned char factorChar);
};

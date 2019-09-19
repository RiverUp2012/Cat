
#include "../GameLibInclude/glHashHelper.h"
#include "../GameLibInclude/glString.h"

unsigned int glHashHelper::hashElfA(const char * string, const int charsToHash) {
	unsigned int hash = 0;
	unsigned int lastBit = 0;
	int charsToHashTemp = 0;
	if (string) {
		charsToHashTemp = charsToHash > 0 ? charsToHash : glStringA::getLength(string);
		for (int i = 0; i < charsToHashTemp; ++i) {
			hash = (hash << 4) + string[i];
			lastBit = hash & 0x80000000;
			if (lastBit) {
				hash ^= (lastBit >> 24);
				hash &= ~lastBit;
			}
		}
	}
	return hash;
}

unsigned int glHashHelper::hashElfW(const wchar_t * string, const int charsToHash) {
	unsigned int hash = 0;
	unsigned int lastBit = 0;
	int charsToHashTemp = 0;
	if (string) {
		charsToHashTemp = charsToHash > 0 ? charsToHash : glStringW::getLength(string);
		for (int i = 0; i < charsToHashTemp; ++i) {
			hash = (hash << 4) + string[i];
			lastBit = hash & 0x80000000;
			if (lastBit) {
				hash ^= (lastBit >> 24);
				hash &= ~lastBit;
			}
		}
	}
	return hash;
}

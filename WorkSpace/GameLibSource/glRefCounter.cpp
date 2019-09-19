
#include "../GameLibInclude/glRefCounter.h"

glRefCounter::glRefCounter() {
	mRefCount = 1;
}

glRefCounter::~glRefCounter() {

}

void glRefCounter::addRef(void) {
	++mRefCount;
}

bool glRefCounter::release(void) {
	--mRefCount;
	if (mRefCount <= 0) {
		delete this;
		return true;
	}
	return false;
}

int glRefCounter::getRefCount(void) const {
	return mRefCount;
}

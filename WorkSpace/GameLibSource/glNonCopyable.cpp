
#include "../GameLibInclude/glNonCopyable.h"

glNonCopyable::glNonCopyable() {

}

glNonCopyable::~glNonCopyable() {

}

glNonCopyable::glNonCopyable(const glNonCopyable &) {

}

glNonCopyable & glNonCopyable::operator=(const glNonCopyable &) {
	return *this;
}


#include "../WinLib.h"

wlNonCopyable::wlNonCopyable() {

}

wlNonCopyable::~wlNonCopyable() {

}

wlNonCopyable::wlNonCopyable(const wlNonCopyable & other) {

}

wlNonCopyable & wlNonCopyable::operator=(const wlNonCopyable & other) {
	return *this;
}

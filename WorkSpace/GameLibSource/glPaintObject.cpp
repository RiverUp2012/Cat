
#include "../GameLibInclude/glPaintObject.h"

glPaintObject::glPaintObject() {
	mVisible = true;
}

glPaintObject::~glPaintObject() {

}

void glPaintObject::setPos(const glPoint<float> & pos) {
	mPos = pos;
}

const glPoint<float> & glPaintObject::getPos(void) const {
	return mPos;
}

void glPaintObject::setSize(const glSize<float> & size) {
	mSize = size;
}

const glSize<float> & glPaintObject::getSize(void) const {
	return mSize;
}

glRect<float> glPaintObject::getBoundBox(void) const {
	return glRect<float>(mPos, mSize);
}

void glPaintObject::setVisible(const bool visible) {
	mVisible = visible;
}

bool glPaintObject::getVisible(void) const {
	return mVisible;
}

void glPaintObject::onPaint(const glPoint<float> & parentPos) {

}

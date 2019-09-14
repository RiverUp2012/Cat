
#include "../SurgeGameEngine.h"

sgePaintObject::sgePaintObject()
{
	mVisible = true;
}

sgePaintObject::~sgePaintObject()
{

}

void sgePaintObject::setPos(const sgePoint<float> & pos)
{
	mPos = pos;
}

const sgePoint<float> & sgePaintObject::getPos(void) const
{
	return mPos;
}

void sgePaintObject::setSize(const sgeSize<float> & size)
{
	mSize = size;
}

const sgeSize<float> & sgePaintObject::getSize(void) const
{
	return mSize;
}

sgeRect<float> sgePaintObject::getBoundBox(void) const
{
	return sgeRect<float>(mPos, mSize);
}

void sgePaintObject::setVisible(const bool visible)
{
	mVisible = visible;
}

bool sgePaintObject::getVisible(void) const
{
	return mVisible;
}

void sgePaintObject::onPaint(const sgePoint<float> & parentPos)
{

}

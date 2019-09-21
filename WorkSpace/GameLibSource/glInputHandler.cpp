
#include "../GameLibInclude/glInputHandler.h"

glInputHandler::glInputHandler()
{
	mHandleInputEvent = true;
}

glInputHandler::~glInputHandler()
{

}

void glInputHandler::setHandleInputEvent(const bool handleInputEvent)
{
	mHandleInputEvent = handleInputEvent;
}

bool glInputHandler::getHandleInputEvent(void) const
{
	return mHandleInputEvent;
}

bool glInputHandler::onMouseMove(const int, const int) {
	return true;
}

bool glInputHandler::onKeyUp(const int) {
	return true;
}

bool glInputHandler::onKeyDown(const int) {
	return true;
}

bool glInputHandler::onMouseWhellUp(void) {
	return true;
}

bool glInputHandler::onMouseWhellDown(void) {
	return true;
}

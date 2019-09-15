
#include "../GameLib.h"

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

bool glInputHandler::handleInput(
	const glInputType inputType,
	const glPoint<int> & mousePos,
	const int keyCode)
{
	return true;
}

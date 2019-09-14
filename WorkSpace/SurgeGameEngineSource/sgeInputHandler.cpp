
#include "../SurgeGameEngine.h"

sgeInputHandler::sgeInputHandler()
{
	mHandleInputEvent = true;
}

sgeInputHandler::~sgeInputHandler()
{

}

void sgeInputHandler::setHandleInputEvent(const bool handleInputEvent)
{
	mHandleInputEvent = handleInputEvent;
}

bool sgeInputHandler::getHandleInputEvent(void) const
{
	return mHandleInputEvent;
}

bool sgeInputHandler::handleInput(
	const sgeInputType inputType,
	const sgePoint<int> & mousePos,
	const int keyCode)
{
	return true;
}

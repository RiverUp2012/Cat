
#include "../GameLibInclude/glTimer.h"
#include "../GameLibInclude/glTimerSystem.h"

glTimer::glTimer() {

}

glTimer::~glTimer() {
	unregisterTimer();
}

bool glTimer::registerTimer(const int timerID, const int duration) {
	return glTimerSystem::registerTimer(this, timerID, duration);
}

bool glTimer::unregisterTimer(const int timerID) {
	return glTimerSystem::unregisterTimer(this, timerID);
}

bool glTimer::unregisterTimer(void) {
	return glTimerSystem::unregisterTimer(this);
}

void glTimer::onTimer(const int timerID) {

}

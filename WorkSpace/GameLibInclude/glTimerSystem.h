
#pragma once

class glTimer;

//
// @brief 定时器系统类
//
class glTimerSystem {
public:
	static bool registerTimer(glTimer * timer, const int timerID, const int duration);
	static bool unregisterTimer(glTimer * timer, const int timerID);
	static bool unregisterTimer(glTimer * timer);
	static void quit(void);
};

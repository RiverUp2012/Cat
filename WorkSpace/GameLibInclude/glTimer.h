
#pragma once

//
// @brief ¶¨Ê±Æ÷Àà
//
class glTimer {
public:
	glTimer();
	virtual ~glTimer();
public:
	bool registerTimer(const int timerID, const int duration);
	bool unregisterTimer(const int timerID);
	bool unregisterTimer(void);
public:
	virtual void onTimer(const int timerID) = 0;
};

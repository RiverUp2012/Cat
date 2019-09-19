
#pragma once

//
// @brief 输入处理器类
//
class glInputHandler {
public:
	glInputHandler();
	virtual ~glInputHandler();
public:
	void setHandleInputEvent(const bool handleInputEvent);
	bool getHandleInputEvent(void) const;
public:
	virtual bool onMouseMove(const int mouseX, const int mouseY);
	virtual bool onKeyUp(const int keyCode);
	virtual bool onKeyDown(const int keyCode);
	virtual bool onMouseWhellUp(void);
	virtual bool onMouseWhellDown(void);
private:
	bool mHandleInputEvent;
};

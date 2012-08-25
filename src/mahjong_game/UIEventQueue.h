#ifndef UIEVENTQUEUE_H_
#define UIEVENTQUEUE_H_

#include <queue>

class UIEvent{
public:
	virtual ~UIEvent() {}
	virtual std::string toString()= 0;
} ;

class UIEventQueue {
public:
	UIEventQueue();
	virtual ~UIEventQueue();
	UIEvent * popEvent();
	void addEvent(UIEvent * event);

private:
	std::queue<UIEvent*> eventQueue_;
};

#endif /* UIEVENTQUEUE_H_ */

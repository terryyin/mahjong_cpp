#include "mahjong_game.h"
#include "UIEvent.h"

UIEventQueue::UIEventQueue() {
}

UIEventQueue::~UIEventQueue() {
}

UIEvent * UIEventQueue::popEvent() {
	if (eventQueue_.empty())
		return NULL;
	UIEvent *event = eventQueue_.front();
	eventQueue_.pop();
	return event;
}

void UIEventQueue::addEvent(UIEvent * event) {
	eventQueue_.push(event);
}

#ifndef HTMLUIEVENT_H_
#define HTMLUIEVENT_H_

#include "UIEventQueue.h"
#include <string>

class HTMLPickEvent: public UIEvent {
public:
	HTMLPickEvent(tile_t tile, int distance) :
			tile_(tile), distance_(distance) {
	}
	virtual ~HTMLPickEvent() {
	}
	virtual std::string toString();
private:
	tile_t tile_;
	int distance_;
};

class HTMLEnableWinEvent: public UIEvent {
public:
	virtual std::string toString();
};

class HTMLDiscardEvent: public UIEvent {
public:
	HTMLDiscardEvent(tile_t tile, int distance):
		tile_(tile), distance_(distance) {}
	std::string toString();
private:
	tile_t tile_;
	int distance_;
};

class HTMLWinEvent: public UIEvent {
public:
	HTMLWinEvent(int distance, int score): distance_(distance), score_(score) {}
	std::string toString();
private:
	int distance_;
	int score_;
};

class HTMLMessageEvent: public UIEvent {
public:
	HTMLMessageEvent(const char * message) {message_ = message;}
	std::string toString();
private:
	const char * message_;
};

class HTMLEnablePongEvent: public UIEvent {
public:
	std::string toString();
};

class HTMLEnableChewEvent: public UIEvent {
public:
	std::string toString();
};

class HTMLEventFactory {
public:
	UIEvent * createPickEvent(tile_t tile, int distance);
	UIEvent * createDiscardEvent(tile_t tile, int distance);
	UIEvent * createEnableWinEvent();
	UIEvent * createWinEvent(int distance, int score);
	UIEvent * createMessageEvent(const char * message);
	UIEvent * createEnablePongEvent();
	UIEvent * createEnableChewEvent();
};

#endif /* HTMLUIEVENT_H_ */

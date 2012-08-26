#include "mahjong_game.h"
#include "HTMLUIEvent.h"

using namespace std;

string HTMLPickEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "App.Pick(%d, %d);", distance_, tile_);
	if (0 != distance_)
		strcat(tmp, "|");

	return tmp;
}

string HTMLDiscardEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "App.Throw(%d, %d);", tile_, distance_);
	if (0 == distance_)
		strcat(tmp, "|");

	return tmp;
}

string HTMLEnableWinEvent::toString() {
	return "App.LightButton('win');";
}

string HTMLWinEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "App.WinAck(%d, %d);", distance_, score_);
	return tmp;
}

string HTMLMessageEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "alert(\"%s\");", message_);
	return tmp;
}

string HTMLEnablePongEvent::toString() {
	return "App.LightButton('pong');";
}

string HTMLEnableChewEvent::toString() {
	return "App.LightButton('chew');";
}

UIEvent * HTMLEventFactory::createPickEvent(tile_t tile, int distance) {
	return new HTMLPickEvent(tile, distance);
}

UIEvent * HTMLEventFactory::createEnableWinEvent() {
	return new HTMLEnableWinEvent();
}

UIEvent * HTMLEventFactory::createDiscardEvent(tile_t tile, int distance) {
	return new HTMLDiscardEvent(tile, distance);
}

UIEvent * HTMLEventFactory::createWinEvent(int distance, int score) {
	return new HTMLWinEvent(distance, score);
}

UIEvent * HTMLEventFactory::createMessageEvent(const char * message) {
	return new HTMLMessageEvent(message);
}

UIEvent * HTMLEventFactory::createEnablePongEvent() {
	return new HTMLEnablePongEvent();
}

UIEvent * HTMLEventFactory::createEnableChewEvent() {
	return new HTMLEnableChewEvent();
}

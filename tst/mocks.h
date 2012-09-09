#ifndef MOCKS_H_
#define MOCKS_H_

class Perspective;
class EvaluatorAdaptor;
EvaluatorAdaptor * createMockEvaluator(void);

#include "Perspective.h"
#include "tiles.h"
class MockPerspective: public Perspective {
public:
	virtual void destroy(Perspective *self) {
		free(self);
	}

	virtual void deal(tile_t tiles[], int buffer_size, int distance) {
		char s[100];
		mock().actualCall("deal").onObject(this).withParameter("distance",
				distance).withParameter("tiles",
				tiles_to_string(tiles, buffer_size, s, 100));
	}

	virtual void pick(tile_t tile, int distance) {
		mock().actualCall("pick").onObject(this).withParameter("tile",
				tile).withParameter("distance", distance);
	}

	virtual void win(int score, int distance) {
		mock().actualCall("win").onObject(this).withParameter("score",
				score).withParameter("distance", distance);
	}

	virtual void discard(tile_t tile, int distance) {
		mock().actualCall("discard_tile").onObject(this).withParameter(
				"tile", tile).withParameter("distance", distance);
	}
	virtual void pong(tile_t tile, int distance) {
	}

	virtual int chow(tile_t tile, tile_t with, int distance) {
		return 0;
	}

	virtual void pushActionRequest(PlayerActionRequest *actionRequest) {
	}
};

#include "HTMLMahjongGameRespond.h"
class MockHTMLMahjongGameRespond: public HTMLMahjongGameRespond {
public:
	void newGame(int gameID) {
		mock().actualCall("newHTMLFrame").onObject(this).withParameter("gameID",
				gameID);
	}

	void bye() {
		mock().actualCall("bye").onObject(this);
	}

	void shutdown() {
		mock().actualCall("shutdown").onObject(this);
	}

	void updateUIEvent(UserView *view) {
		mock().actualCall("updateUIEvent").onObject(this).withParameter("view",
				view);
	}

	void gameDoesNotExist() {
		mock().actualCall("gameDoesNotExist").onObject(this);
	}

	void updateAllHoldings(UserView *view) {
		mock().actualCall("updateAllHoldings").onObject(this).withParameter(
				"view", view);
	}

};

class MockHTMLMahjongGameServer: public HTMLMahjongGameServer {
public:
	GameID startNewGame() {
		return mock().actualCall("startNewGame").onObject(this).returnValue().getIntValue();
	}

	void killGame(GameID gameID) {
		mock().actualCall("killGame").onObject(this).withParameter("gameID",
				gameID);
	}

	void shutdown() {
		mock().actualCall("shutdown").onObject(this);
	}

	Game * getGameByID(GameID gameID) {
		return (Game*) mock().actualCall("getGameByID").onObject(this).withParameter(
				"gameID", gameID).returnValue().getObjectPointer();
	}

};

#include "game.h"
class MockGame: public Game {
public:
	virtual void nextMove(PlayerActionRequest *request) {
		mock().actualCall("nextMove").onObject(this).withParameter("request", request);
	}

	virtual void setAction(PlayerActionRequest * actionRequest) {
		mock().actualCall("set_action").onObject(this);
	}

	virtual UserView *getUserView() {
		return (UserView *) mock().actualCall("getUserView").onObject(this).returnValue().getPointerValue();
	}

};

#include "UserPerspective.h"
class MockUserView: public UserView {
public:
	UIEvent * popEvent() {
		return (UIEvent *) mock().actualCall("popEvent").onObject(this).returnValue().getObjectPointer();
	}

	const char * get_tiles_array_string(char buffer[], int buffer_size) {
		return "<tile list>";
	}

	int getNumberOfPlayer() {
		return mock().actualCall("getNumberOfPlayer").onObject(this).returnValue().getIntValue();
	}

	Hand *getHand(int distance) {
		return (Hand *) mock().actualCall("getPlayerData").onObject(this).returnValue().getObjectPointer();
	}
};

#include "UIEvent.h"
class MockUIEventFactory: public UIEventFactory {
public:
	virtual ~MockUIEventFactory() {
	}

	virtual UIEvent * createPickEvent(tile_t tile, int distance) {
		return (UIEvent *) mock().actualCall("createPickEvent").withParameter(
				"tile", tile).withParameter("distance", distance).returnValue().getObjectPointer();
	}

	virtual UIEvent * createDiscardEvent(tile_t tile, int distance) {
		return (UIEvent *) mock().actualCall("createDiscardEvent").withParameter(
				"tile", tile).withParameter("distance", distance).returnValue().getObjectPointer();
	}

	virtual UIEvent * createEnableWinEvent() {
		return (UIEvent *) mock().actualCall("createEnableWinEvent").returnValue().getObjectPointer();
	}

	virtual UIEvent * createWinEvent(int distance, int score) {
		return (UIEvent *) mock().actualCall("createWinEvent").withParameter(
				"score", score).withParameter("distance", distance).returnValue().getObjectPointer();
	}

	virtual UIEvent * createMessageEvent(const char * message) {
		return (UIEvent *) mock().actualCall("createMessageEvent").withParameter(
				"message", message).returnValue().getObjectPointer();
	}

	virtual UIEvent * createEnablePongEvent() {
		return (UIEvent *) mock().actualCall("createEnablePongEvent").returnValue().getObjectPointer();
	}

	virtual UIEvent * createEnableChewEvent() {
		return (UIEvent *) mock().actualCall("createEnableChewEvent").returnValue().getObjectPointer();
	}

	virtual UIEvent * createDealEvent(UserView * view) {
		return (UIEvent *) mock().actualCall("createDealEvent").withParameter(
				"view", view).returnValue().getObjectPointer();
	}
};

#endif /* MOCKS_H_ */

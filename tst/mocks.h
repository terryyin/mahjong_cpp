#ifndef MOCKS_H_
#define MOCKS_H_

class Perspective;
class Evaluator;
void setup_tile_pool_mocks(void);
Perspective * createMockPerspective(void);
Evaluator * createMockEvaluator(void);

#include "HTMLMahjongGameRespond.h"
class MockHTMLMahjongGameRespond: public MahjongGameRespond {
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
		mock().actualCall("updateUIEvent").onObject(this).withParameter("view", view);
	}

	void gameDoesNotExist() {
		mock().actualCall("gameDoesNotExist").onObject(this);
	}

	void updateAllHoldings(UserView *view) {
		mock().actualCall("updateAllHoldings").onObject(this).withParameter("view", view);
	}

	void setString(const char * string) {
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
class MockGame : public Game {
public:
	virtual void update() {
		mock().actualCall("update").onObject(this);
	}

	virtual void set_action(action_t action, tile_t tile) {
		mock().actualCall("set_action").onObject(this);
	}

	virtual UserView *getUserView() {
		return (UserView *)mock().actualCall("getUserView").onObject(this).returnValue().getPointerValue();
	}

};

#include "UserPerspective.h"
class MockUserView : public UserView {
public:
	UIEvent * popEvent() {
		return (UIEvent *)mock().actualCall("popEvent").onObject(this).returnValue().getObjectPointer();
	}
	const char * get_tiles_array_string(char buffer[], int buffer_size) {
		return "<tile list>";
	}
};

#endif /* MOCKS_H_ */

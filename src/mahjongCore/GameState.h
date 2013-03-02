#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "tile.h"
class MahjongTable;
class GameState {
public:
	GameState(MahjongTable * table);
	virtual ~GameState();
	virtual void restart() {
	}
	virtual void doWin() {
	}
	virtual void doPick() {
	}
	virtual void discard(Tile& action_tile) {
		UNUSED(action_tile);
	}
	virtual void doPong() {
	}
	virtual void doChow(Tile& action_tile) {
		UNUSED(action_tile);
	}
protected:
	MahjongTable * getTable() {
		return table_;
	}
private:
	MahjongTable * table_;
};

class GameStateEndOfGame: public GameState {
public:
	GameStateEndOfGame(MahjongTable * table) :
			GameState(table) {
	}
	void restart();
};

class GameStatePicked: public GameState {
public:
	GameStatePicked(MahjongTable * table) :
			GameState(table) {
	}

	void discard(Tile& action_tile);
	void doWin();
};

class GameStatePicking: public GameState {
public:
	GameStatePicking(MahjongTable * table) :
			GameState(table) {
	}
	void doPick();
	void doWin();
	void doPong();
	void doChow(Tile& action_tile);
};

#endif /* GAMESTATE_H_ */

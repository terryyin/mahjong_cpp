#ifndef GAME_FLOW_H_
#define GAME_FLOW_H_

#include "tile.h"
#include "GameState.h"

class Wall;
class Hand;
class Perspective;
class PlayerActionRequest;

class MahjongTable{
public:
	MahjongTable(Wall * wall);

	~MahjongTable();

	void nextMove();

	void addPlayer(Perspective * player);

private:
	Perspective * getPlayerOfDistance( int i);
	int getPlayerCount();
	void pick( tile_t tile);
	void changeHost();
	void changeCurrentPlayer( int distance);
	void win( int score);
	void deal( tile_t tiles[], int n);
	void throw_tile( tile_t tile);
	void pong();
	int chow( tile_t with);
	void restartGameWhenAllPlayersAreReady();
	void restartGame();
	PlayerActionRequest popActionRequest();
	void discard(tile_t& action_tile);
	void doWin();
	void doPick();
	void doPong();
	void doChow(tile_t action_tile);

	Wall *wall_;
	Perspective * players[MAX_NUMBER_OF_PLAYER];
	int player_count_;
	int current_player;
	int host;
	tile_t last_tile;
	int restartCount_;
	GameState * currentState_;
	GameStateEndOfGame endOfGameState_;
	GameStatePicked pickedState_;
	GameStatePicking pickingState_;

	friend class GameStateEndOfGame;
	friend class GameStatePicked;
	friend class GameStatePicking;
};

#endif /* GAME_FLOW_H_ */

#ifndef GAME_FLOW_H_
#define GAME_FLOW_H_

#include "tile.h"

class TilePool;
class PlayerTiles;
class Perspective;

typedef enum {
	GAME_PICKED,
	GAME_WAITING,
	GAME_PICKING,
	GAME_END
} game_state_t;

class MahjongTable{
public:
	MahjongTable(TilePool *pool);

	~MahjongTable();

	void nextMove();

	void addPlayer(Perspective * player);

	bool doPlayerAction();

private:
	Perspective * get_player_of_distance( int i);
	int get_player_count();
	void pick( tile_t tile);
	void change_host();
	void change_current_player( int distance);
	void win( int score);
	void deal( tile_t tiles[], int n);
	void throw_tile( tile_t tile);
	void pong();
	int chow( tile_t with);
	void restartGameWhenAllPlayersAreReady();
	TilePool *tile_pool;
	game_state_t state;
	Perspective * players[MAX_NUMBER_OF_PLAYER];
	int player_count;
	int current_player;
	int host;
	tile_t last_tile;
	int more_useless_stuff;
};

#endif /* GAME_FLOW_H_ */

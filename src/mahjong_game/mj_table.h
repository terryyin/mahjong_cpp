#ifndef GAME_FLOW_H_
#define GAME_FLOW_H_

#include "tile.h"

class tile_pool_t;
class PlayerData;
class Perspective;

typedef enum {
	GAME_PICKED,
	GAME_WAITING,
	GAME_PICKING,
	GAME_END
} game_state_t;

struct dispatcher_t;
class MahjongTable{
public:
	MahjongTable(tile_pool_t *pool);
	~MahjongTable();
	void remove_agent(Perspective * agent);
	game_state_t get_state();
	void update_state();
	void add_player(Perspective * player);
	void setPool(tile_pool_t * pool);
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
	tile_pool_t *tile_pool;
	game_state_t state;
	Perspective * players[MAX_NUMBER_OF_PLAYER];
	int player_count;
	int current_player;
	int host;
	tile_t last_tile;
	int more_useless_stuff;
};

MahjongTable * create_mj_table(tile_pool_t *game);

#endif /* GAME_FLOW_H_ */

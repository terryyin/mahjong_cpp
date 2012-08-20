#ifndef GAME_FLOW_H_
#define GAME_FLOW_H_

#include "tile.h"

typedef struct tile_pool_t * tile_pool_ptr_t;
struct player_t;
class Agent;

typedef enum {
	GAME_PICKED,
	GAME_WAITING,
	GAME_PICKING,
	GAME_END
} game_state_t;

struct dispatcher_t;
class mj_table_t{
public:
	tile_pool_ptr_t tile_pool;
	game_state_t state;
	Agent * players[MAX_NUMBER_OF_PLAYER];
	int player_count;
	int current_player;
	int host;
	tile_t last_tile;
	int more_useless_stuff;
};

mj_table_t * create_mj_table(tile_pool_ptr_t game);
void mj_table_remove_agent(mj_table_t * self, Agent * agent);
void mj_table_destroy(mj_table_t * self);
game_state_t mj_table_get_state(mj_table_t * self);
void mj_table_update_state(mj_table_t * self);
void mj_table_add_player(mj_table_t * self,
		Agent * player);

#endif /* GAME_FLOW_H_ */

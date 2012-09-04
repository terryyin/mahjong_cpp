#ifndef PLAYER_H_
#define PLAYER_H_

#define MAX_EATEN_COUNT (MAX_HOLDING_COUNT/3)

#include "tiles.h"

class Hand {
public:
	Hand();
	~Hand();
	int get_holdings(tile_t * tiles_buffer, int buffer_size);
	int get_eaten(eaten_t * tiles_buffer, int buffer_size);
	tile_t get_current();

	void pick(tile_t);
	void pong(tile_t);
	int chow(tile_t tile, tile_t with);
	tile_t discard_tile(tile_t tile);
	void deal(tile_t tiles[], int tiles_count);

	int is_able_to_pong(tile_t tile);
	int is_able_to_chow(tile_t tile);
	int is_able_to_win(tile_t tile);
private:
	void sort();
	void rearrange_after_eat(eaten_t eaten);
	int is_able_to_chow(tile_t tile, tile_t smallest);
	void _chow(tile_t tile, tile_t smallest);
private:
	tile_t holdings[MAX_HOLDING_COUNT];
	eaten_t eaten[MAX_EATEN_COUNT];
	tile_t current;
};

Hand * create_player_data(void);

#endif /* PLAYER_H_ */

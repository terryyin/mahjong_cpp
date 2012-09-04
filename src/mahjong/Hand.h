#ifndef PLAYER_H_
#define PLAYER_H_

#define MAX_meld_COUNT (MAX_HOLDING_COUNT/3)

#include "tiles.h"

class Hand {
public:
	Hand();
	~Hand();
	int getHoldings(tile_t * tiles_buffer, int buffer_size);
	int getMelds(meld_t * tiles_buffer, int buffer_size);
	tile_t getCurrentTileAtHand();

	void pick(tile_t);
	void pong(tile_t);
	int chow(tile_t tile, tile_t with);
	tile_t discard_tile(tile_t tile);
	void deal(tile_t tiles[], int tiles_count);

	int isAbleToPong(tile_t tile);
	int isAbleToChow(tile_t tile);
	int isAbleToWin(tile_t tile);
private:
	void sort();
	void rearrange_after_eat(meld_t meld);
	int is_able_to_chow(tile_t tile, tile_t smallest);
	void _chow(tile_t tile, tile_t smallest);
private:
	tile_t holdings[MAX_HOLDING_COUNT];
	meld_t meld[MAX_meld_COUNT];
	tile_t current;
};

Hand * createHand(void);

#endif /* PLAYER_H_ */

#ifndef GAME__H
#define GAME__H

#include "tiles.h"

#define ALL_COUNT 134
#define MAX_PICKS 70

class tile_pool_t {
public:
	tile_pool_t();
	virtual ~tile_pool_t();
	virtual void shuffle();
	virtual int is_end();
	virtual tile_t pop_a_tile();
private:
	void _init();
	void _swap(int index1, int index2);
	tile_t uncovered_tiles[ALL_COUNT];
	int picks_count;
};

extern tile_pool_t * (*create_tile_pool)(void);

#endif

#include <stdlib.h>
#include <string.h>
#include "tile_pool.h"

static const tile_t all_types[] = { C(1), C(2), C(3), C(4), C(5), C(6), C(7),
		C(8), C(9), R(1), R(2), R(3), R(4), R(5), R(6), R(7), R(8), R(9),
		B(1), B(2), B(3), B(4), B(5), B(6), B(7), B(8), B(9), MJ_EAST,
		MJ_SOUTH, MJ_WEST, MJ_NORTH, MJ_ZHONG, MJ_FA, MJ_BAI };
/*
static const tile_t all_types[] = {R(1), R(2), R(3), R(4), R(5), R(6), R(7), R(8), R(9),
		B(1), B(2), B(3), B(4), B(5), B(6), B(7), B(8), B(9)};
*/
#define TILE_TYPES sizeof(all_types)/sizeof(all_types[0])

tile_pool_t * create_tile_pool() {
	return new tile_pool_t;
}

tile_pool_t::tile_pool_t() {
	_init();
}
void tile_pool_t::_init() {
	int cnt = 0;
	int i = 0, j;

	for (j = 0; j < 4; j++)
		for (i = 0; i < TILE_TYPES; i++)
			this->uncovered_tiles[cnt++] = all_types[i];
	this->picks_count = 0;
}

#define SHUFFLE_TIMES 1000
static int random_index() {
	return rand() % ALL_COUNT;
}

void tile_pool_t::_swap(int index1, int index2) {
	tile_t temp = this->uncovered_tiles[index1];
	this->uncovered_tiles[index1] = this->uncovered_tiles[index2];
	this->uncovered_tiles[index2] = temp;
}

void tile_pool_t::shuffle() {
	_init();

	int i;
	for (i = 0; i < SHUFFLE_TIMES; i++)
		_swap(random_index(), random_index());
}

tile_t tile_pool_t::pop_a_tile() {
	return uncovered_tiles[picks_count++];
}

tile_pool_t::~tile_pool_t() {
}

int tile_pool_t::is_end() {
	return this->picks_count >= MAX_PICKS;
}


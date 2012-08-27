#include "TilePool.h"

/*
 * SIMPLIFIED_MAHJONG is for people who cannot recognize Chinese characters.
 */
#ifndef SIMPLIFIED_MAHJONG
static const tile_t all_types[] = { C(1), C(2), C(3), C(4), C(5), C(6), C(7),
		C(8), C(9), R(1), R(2), R(3), R(4), R(5), R(6), R(7), R(8), R(9),
		B(1), B(2), B(3), B(4), B(5), B(6), B(7), B(8), B(9), MJ_EAST,
		MJ_SOUTH, MJ_WEST, MJ_NORTH, MJ_ZHONG, MJ_FA, MJ_BAI };
#else
static const tile_t all_types[] = {R(1), R(2), R(3), R(4), R(5), R(6), R(7), R(8), R(9),
		B(1), B(2), B(3), B(4), B(5), B(6), B(7), B(8), B(9)};
#endif

#define TILE_TYPES sizeof(all_types)/sizeof(all_types[0])

static TilePool * create_tile_pool_impl() {
	return new TilePool;
}

TilePool * (*create_tile_pool)() = create_tile_pool_impl;

TilePool::TilePool() {
	_init();
}
void TilePool::_init() {
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

void TilePool::_swap(int index1, int index2) {
	tile_t temp = this->uncovered_tiles[index1];
	this->uncovered_tiles[index1] = this->uncovered_tiles[index2];
	this->uncovered_tiles[index2] = temp;
}

void TilePool::shuffle() {
	_init();

	int i;
	for (i = 0; i < SHUFFLE_TIMES; i++)
		_swap(random_index(), random_index());
}

tile_t TilePool::pop_a_tile() {
	return uncovered_tiles[picks_count++];
}

TilePool::~TilePool() {
}

int TilePool::is_end() {
	return this->picks_count >= MAX_PICKS;
}


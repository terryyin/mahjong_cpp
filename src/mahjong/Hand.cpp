#include "Hand.h"
#include "memory.h"
#include <stdlib.h>
#include "Perspective.h"

Hand::~Hand() {
}
void Hand::pick(tile_t tile) {
	this->current = tile;
}

void Hand::sort() {
	tiles_sort(this->holdings, MAX_HOLDING_COUNT);
}

int Hand::is_able_to_win(tile_t discard) {
	if (discard == NO_TILE)
		discard = this->current;
	return tiles_plus_one_is_winning(this->holdings, MAX_HOLDING_COUNT, discard);
}

int Hand::get_holdings(tile_t * tiles_buffer, int buffer_size) {
	int tile_count = tiles_get_count(this->holdings, MAX_HOLDING_COUNT);
	memcpy(tiles_buffer, this->holdings, tile_count * sizeof(tile_t));
	return tile_count;
}

int Hand::get_eaten(eaten_t * tiles_buffer, int buffer_size) {
	int tile_count = 0;
	for (; tile_count < MAX_EATEN_COUNT; tile_count++) {
		if (this->eaten[tile_count])
			tiles_buffer[tile_count] = this->eaten[tile_count];
		else
			break;
	}
	return tile_count;
}

tile_t Hand::get_current() {
	return this->current;
}

void Hand::deal(tile_t tiles[], int buffer_size) {
	int i = 0;
	for (i = 0; i < MAX_HOLDING_COUNT; i++)
		this->holdings[i] = NO_TILE;
	for (i = 0; i < MAX_EATEN_COUNT; i++)
		this->eaten[i] = 0;
	for (i = 0; i < buffer_size; i++)
		this->holdings[i] = tiles[i];
	sort();
}

tile_t Hand::discard_tile(tile_t tile) {
	if (tile == this->current) {
		this->current = NO_TILE;
		return tile;
	} else {
		int i;
		for (i = 0; i < MAX_HOLDING_COUNT; i++) {
			if (this->holdings[i] == tile)
				break;
		}
		if (i < MAX_HOLDING_COUNT) {
			this->holdings[i] = this->current;
			this->current = NO_TILE;
			sort();
			return tile;
		}
	}

	return NO_TILE;
}
int Hand::is_able_to_pong(tile_t tile) {
	return tiles_is_able_to_pong(this->holdings, MAX_HOLDING_COUNT, tile);
}

int Hand::is_able_to_chow(tile_t tile) {
	return tiles_is_able_to_chow(this->holdings, MAX_HOLDING_COUNT, tile);
}

void Hand::rearrange_after_eat(eaten_t eaten) {
	int i, cnt;

	sort();
	cnt = tiles_get_count(this->holdings, MAX_HOLDING_COUNT);
	this->current = this->holdings[cnt - 1];
	this->holdings[cnt - 1] = NO_TILE;

	for (i = 0; i < MAX_EATEN_COUNT; i++) {
		if (this->eaten[i] == 0)
			break;
	}
	this->eaten[i] = eaten;
}

void Hand::pong(tile_t tile) {
	int i, cnt = 0;
	for (i = 0; i < MAX_HOLDING_COUNT; i++) {
		if (this->holdings[i] == tile && cnt < 2) {
			this->holdings[i] = NO_TILE;
			cnt++;
		}
	}
	rearrange_after_eat(PONG(tile));
}

int Hand::is_able_to_chow(tile_t tile, tile_t smallest)
{
	int i, cnt;
	if (tile > smallest + 2)
		return 0;
	cnt = tiles_get_count(this->holdings, MAX_HOLDING_COUNT);
	for (i = 0; i < 3; i++)
		if (tile != smallest + i)
			if (tiles_get_index_of_tile(this->holdings, cnt, smallest + i)
					== -1)
				return 0;
	return 1;
}
void Hand::_chow(tile_t tile, tile_t smallest)
{
	int i, cnt = 0;
	cnt = tiles_get_count(this->holdings, MAX_HOLDING_COUNT);
	for (i = 0; i < 3; i++)
		if (tile != smallest + i)
			this->holdings[tiles_get_index_of_tile(this->holdings, cnt,
					smallest + i)] = NO_TILE;

	rearrange_after_eat(CHOW(smallest));
}

int Hand::chow(tile_t tile, tile_t with) {
	tile_t smallest = tile < with ? tile : with;
	if (!is_able_to_chow(tile, smallest))
		return 0;
	_chow(tile, smallest);
	return 1;
}

Hand::Hand() {
	int i;
	current = NO_TILE;
	for (i = 0; i < MAX_HOLDING_COUNT; i++) {
		holdings[i] = NO_TILE;
	}
	for (i = 0; i < MAX_EATEN_COUNT; i++) {
		eaten[i] = 0;
	}
}

Hand * create_player_data() {
	return new Hand;
}

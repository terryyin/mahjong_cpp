#ifndef TILES__H
#define TILES__H

#define MAX_HOLDING_COUNT 13

#ifndef bool
#define bool int
#endif

#include "tile_t.h"

bool tiles_is_able_to_chow(tile_t tiles[], int size_of_array, tile_t tile);
int tiles_get_count(tile_t tiles[], int size_of_array);
int tiles_get_index_of_tile(tile_t tiles[], int n, tile_t tile);
void tiles_sort(tile_t tiles[], int n);
bool tiles_is_able_to_pong(tile_t tiles[], int n, tile_t tile);
bool tiles_plus_one_is_winning(tile_t holding[], int n, tile_t discard);

#endif

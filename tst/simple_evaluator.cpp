/*
 * this is an example of Simulator.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tile.h"
#include "evaluator.h"
#include "../mahjong_evaluator/include/mj_evaluator.h"

static tile_t cheapest_tile = NO_TILE;
void set_cheapest_tile(tile_t tile) {
	cheapest_tile = tile;
}

class evaluator_imp_t : public Evaluator {
public:
	virtual int evaluate_array(tile_t tiles[], int array_size){
		int i;
		for(i=0; i < array_size; i++) {
			if (tiles[i]==cheapest_tile)
				return 1;
		}
		return 2;
	}

};

Evaluator * create_simple_evaluator_r() {
	return new evaluator_imp_t();
}


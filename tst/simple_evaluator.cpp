/*
 * this is an example of Simulator.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tile.h"
#include "EvaluatorAdapter.h"

static tile_t cheapest_tile = NO_TILE;
void setCheapestTileForSimpleEvaluator(tile_t tile) {
	cheapest_tile = tile;
}
/*
 * The simple evaluator will always give a hand without
 * the "cheapest_tile" a higher score.
 * Therefore the AI will always choose the cheapest tile to discard.
 */
class evaluator_imp_t : public EvaluatorAdapter {
public:
	virtual int evaluate_array(tile_t tiles[], int array_size){
		for(int i=0; i < array_size; i++) {
			if (tiles[i]==cheapest_tile)
				return 1;
		}
		return 2;
	}

};

EvaluatorAdapter * createSimpleEvaluator() {
	return new evaluator_imp_t();
}


/*
 * this is an example of Simulator.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tile.h"
#include "EvaluatorAdaptor.h"

static Tile cheapest_tile = NO_TILE;
void setCheapestTileForSimpleEvaluator(Tile tile) {
	cheapest_tile = tile;
}
/*
 * The simple evaluator will always give a hand without
 * the "cheapest_tile" a higher score.
 * Therefore the AI will always choose the cheapest tile to discard.
 */
class evaluator_imp_t : public EvaluatorAdaptor {
public:
	virtual int evaluate_array(const TileArray& tiles){
		for(int i=0; i < tiles.getTileCount(); i++) {
			if (tiles[i]==cheapest_tile)
				return 1;
		}
		return 2;
	}
};

EvaluatorAdaptor * createSimpleEvaluator() {
	return new evaluator_imp_t();
}


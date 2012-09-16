#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TileArray.h"
#include "EvaluatorAdaptor.h"
#include "mj_evaluator.h"


class EvaluatorImpl : public EvaluatorAdaptor {
public:
	EvaluatorImpl() {
	}

	~EvaluatorImpl() {
	}

	virtual int evaluate_array(const TileArray& tiles){
		mahjong_evaluator_handle_t handle;
		tile_t rawTiles[tiles.getTileCount()];
		for (int i = 0; i < tiles.getTileCount(); i++)
			rawTiles[i] = tiles[i].getID();
		handle = LIB_create_evaluator();
		int score = LIB_evaluator_evaluate_array(handle, rawTiles, tiles.getTileCount());
		LIB_evaluator_destroy(handle);

		return score;
	}
};


static EvaluatorAdaptor * create_evaluator_impl() {
	return new EvaluatorImpl();
}

EvaluatorAdaptor * (*createEvaluatorAdaptor)(void) = create_evaluator_impl;


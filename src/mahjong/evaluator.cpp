#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tile.h"
#include "EvaluatorAdapter.h"
#include "../mahjong_evaluator/include/mj_evaluator.h"


class EvaluatorImpl : public EvaluatorAdapter {
public:
	EvaluatorImpl() {
	}

	~EvaluatorImpl() {
	}

	virtual int evaluate_array(tile_t tiles[], int array_size){
		mahjong_evaluator_handle_t handle;
		handle = LIB_create_evaluator();
		int score = LIB_evaluator_evaluate_array(handle, tiles, array_size);
		LIB_evaluator_destroy(handle);

		return score;
	}
};


static EvaluatorAdapter * create_evaluator_impl() {
	return new EvaluatorImpl();
}

EvaluatorAdapter * (*createEvaluatorAdapter)(void) = create_evaluator_impl;


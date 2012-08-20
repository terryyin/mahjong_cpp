#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tile.h"
#include "evaluator.h"
#include "../mahjong_evaluator/include/mj_evaluator.h"


class EvaluatorImpl : public Evaluator {
public:
	EvaluatorImpl() {
		this->evalutor = LIB_create_evaluator();
	}
	~EvaluatorImpl() {
		LIB_evaluator_destroy(this->evalutor);
	}
	virtual int evaluate_array(tile_t tiles[], int array_size){
		return LIB_evaluator_evaluate_array(this->evalutor, tiles, array_size);
	}
private:
	Evaluator* evalutor;
};


static Evaluator * create_evaluator_r_impl() {
	return new EvaluatorImpl();
}
Evaluator * (*create_evaluator_r)(void) = create_evaluator_r_impl;

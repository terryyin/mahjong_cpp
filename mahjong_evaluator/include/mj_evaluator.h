/*
 * mj_evaluator.h
 *
 *  Created on: Feb 10, 2011
 *      Author: terry
 */

#ifndef MJ_EVALUATOR_H_
#define MJ_EVALUATOR_H_

#include "tile.h"

#ifdef __cplusplus
extern "C"
{
#endif

class Evaluator;

Evaluator* LIB_create_evaluator(void);
void LIB_evaluator_destroy(Evaluator*);
int LIB_evaluator_evaluate_array(Evaluator* self, tile_t tiles[], int array_size);

#ifdef __cplusplus
}
#endif
#endif /* MJ_EVALUATOR_H_ */

#ifndef EVALUATOR_H_
#define EVALUATOR_H_

#include "TileArray.h"
class EvaluatorAdaptor {
public:
	virtual ~EvaluatorAdaptor() {}
	virtual int evaluate_array(const TileArray& tiles) = 0;
};

extern EvaluatorAdaptor * (*createEvaluatorAdaptor)(void);

#endif /* EVALUATOR_H_ */

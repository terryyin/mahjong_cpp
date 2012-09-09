#ifndef EVALUATOR_H_
#define EVALUATOR_H_

class EvaluatorAdaptor {
public:
	virtual ~EvaluatorAdaptor() {}
	virtual int evaluate_array(tile_t tiles[], int array_size)=0;
};

extern EvaluatorAdaptor * (*createEvaluatorAdaptor)(void);

#endif /* EVALUATOR_H_ */

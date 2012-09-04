#ifndef EVALUATOR_H_
#define EVALUATOR_H_

class EvaluatorAdapter {
public:
	virtual ~EvaluatorAdapter() {}
	virtual int evaluate_array(tile_t tiles[], int array_size)=0;
};

extern EvaluatorAdapter * (*createEvaluatorAdapter)(void);

#endif /* EVALUATOR_H_ */

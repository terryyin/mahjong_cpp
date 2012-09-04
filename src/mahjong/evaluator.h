#ifndef EVALUATOR_H_
#define EVALUATOR_H_

class Evaluator {
public:
	virtual ~Evaluator() {}
	virtual int evaluate_array(tile_t tiles[], int array_size)=0;
};

extern Evaluator * (*create_evaluator_r)(void);

#endif /* EVALUATOR_H_ */

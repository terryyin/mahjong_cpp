#ifndef AI_PERSPECTIVE_H_
#define AI_PERSPECTIVE_H_

#include "Perspective.h"
class Hand;
class Evaluator;
class AIPerspective: public Perspective{
public:
	AIPerspective();
	virtual ~AIPerspective();

	void deal(tile_t tiles[], int n, int distance);
	virtual void pick(tile_t tile, int distance);
	virtual void pong(tile_t tile, int distance);
	virtual int chow(tile_t tile, tile_t with, int distance);
	virtual void win(int score, int distance);
	virtual void discard(tile_t tile, int distance);

	virtual void pushActionRequest(PlayerActionRequest * actionRequest);
	void setEvaluator(Evaluator * evaluator);

private:
	tile_t whichToDiscard();
	Hand * player;
	Evaluator * evaluator;

};

#endif /* AI_PERSPECTIVE_H_ */

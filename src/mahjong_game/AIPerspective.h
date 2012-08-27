#ifndef AI_AGENT_H_
#define AI_AGENT_H_

#include "Perspective.h"
class PlayerTiles;
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
	virtual action_t popActionRequest(tile_t* tile);
	virtual void set_action(action_t action, tile_t tile);
	virtual void discard_tile(tile_t tile, int distance);
	void setEvaluator(Evaluator * evaluator);
private:
	tile_t ai_which_to_discard();
	action_t action;
	tile_t tile;
	PlayerTiles * player;
	Evaluator * evaluator;

};

#endif /* AI_AGENT_H_ */

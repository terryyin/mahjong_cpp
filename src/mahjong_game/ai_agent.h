#ifndef AI_AGENT_H_
#define AI_AGENT_H_

#include "agent.h"
struct player_t;
class Evaluator;
class AIAgent: public Agent{
public:
	AIAgent();
	virtual ~AIAgent();
	void deal(tile_t tiles[], int n, int distance);
	virtual void pick(tile_t tile, int distance);
	virtual void pong(tile_t tile, int distance);
	virtual int chow(tile_t tile, tile_t with, int distance);
	virtual void win(int score, int distance);
	virtual action_t get_action(tile_t* tile);
	virtual void set_action(action_t action, tile_t tile);
	virtual void discard_tile(tile_t tile, int distance);
	void setEvaluator(Evaluator * evaluator);
private:
	tile_t ai_which_to_discard();
	action_t action;
	tile_t tile;
	player_t * player;
	Evaluator * evaluator;

};

AIAgent * create_ai_agent(void);

#endif /* AI_AGENT_H_ */

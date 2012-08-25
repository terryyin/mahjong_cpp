#ifndef SYSTEM_H_
#define SYSTEM_H_


#include "agent.h"
class UIAgent;
class tile_pool_t;
class MahjongTable;
class Game {
public:
	Game();
	virtual ~Game();
	void setTilePool(tile_pool_t* pool);
	UIAgent *getUIAgent();
	virtual void update();
	virtual void set_action(action_t action, tile_t tile);

private:
	tile_pool_t * pool;
	MahjongTable * table;
	Agent * ai_agent;
	UIAgent * agent;
};

#endif /* SYSTEM_H_ */

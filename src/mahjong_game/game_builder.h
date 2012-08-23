#ifndef SYSTEM_H_
#define SYSTEM_H_

struct user_info_t;
class Agent;
class UIAgent;
class tile_pool_t;
class MahjongTable;
class Game {
public:
	Game();
	~Game();
	void setTilePool(tile_pool_t* pool);
	static UIAgent * join_new_game_with_one_ai_player(struct user_info_t * user);

private:
	tile_pool_t * pool;
	MahjongTable * table;
	Agent * ai_agent;
	UIAgent * agent;
};

#endif /* SYSTEM_H_ */

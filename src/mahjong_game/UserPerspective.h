#ifndef UI_AGENT_H_
#define UI_AGENT_H_

#include "tiles.h"
#include "Perspective.h"
#include "UIEventQueue.h"
#include "HTMLUIEvent.h"

class MahjongTable;

class PlayerData;
class Game;

class UserView {
public:
	virtual ~UserView(){};
	virtual UIEvent * popEvent() = 0;
	virtual const char * get_tiles_array_string(char buffer[], int buffer_size) = 0;
};

class UserPerspective: public Perspective, public UserView {
public:
	UserPerspective();
	virtual ~UserPerspective();
	virtual void deal(tile_t tiles[], int n, int distance);
	virtual void pick(tile_t tile, int distance);
	virtual void pong(tile_t tile, int distance);
	virtual int chow(tile_t tile, tile_t with, int distance);
	virtual void win(int score, int distance);
	virtual action_t get_action(tile_t* tile);
	virtual void set_action(action_t action, tile_t tile);
	virtual void discard_tile(tile_t tile, int distance);

	UIEvent * popEvent();
	const char * get_tiles_array_string(char buffer[], int buffer_size);
	void set_game_flow(MahjongTable * game_flow);
	void set_game(Game * game);
	void update_game();
	MahjongTable * getTable();
private:
	void add_event(UIEvent * event);
	void react_after_pick(int distance);
	void react_others_throw(tile_t tile, int distance);

	UIEventQueue eventQueue_;
	action_t action;
	tile_t last_tile;
	tile_t action_tile;
	PlayerData * players[MAX_NUMBER_OF_PLAYER];
	MahjongTable * game_flow;
	Game * game;
	HTMLEventFactory eventFactory_;
	void _remove_players();
};
UserPerspective * createUserPerspective(void);

#endif /* UI_AGENT_H_ */

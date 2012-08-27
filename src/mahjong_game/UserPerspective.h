#ifndef UI_AGENT_H_
#define UI_AGENT_H_

#include "tiles.h"
#include "Perspective.h"
#include "UIEvent.h"

class MahjongTable;

class PlayerTiles;
class Game;

class UserView {
public:
	virtual ~UserView(){};
	virtual UIEvent * popEvent() = 0;
	virtual int getNumberOfPlayer() = 0;
	virtual PlayerTiles *getPlayerData(int distance) = 0;
};

class UserPerspective: public Perspective, public UserView {
public:
	UserPerspective(UIEventFactory *eventFactory = NULL);
	virtual ~UserPerspective();
	virtual void deal(tile_t tiles[], int n, int distance);
	virtual void pick(tile_t tile, int distance);
	virtual void pong(tile_t tile, int distance);
	virtual int chow(tile_t tile, tile_t with, int distance);
	virtual void win(int score, int distance);
	virtual action_t popActionRequest(tile_t* tile);
	virtual void set_action(action_t action, tile_t tile);
	virtual void discard_tile(tile_t tile, int distance);

	virtual UIEvent * popEvent();
	virtual int getNumberOfPlayer();
	virtual PlayerTiles *getPlayerData(int distance);
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
	PlayerTiles * players[MAX_NUMBER_OF_PLAYER];
	MahjongTable * game_flow;
	Game * game;
	UIEventFactory *eventFactory_;
	void _remove_players();
};

#endif /* UI_AGENT_H_ */

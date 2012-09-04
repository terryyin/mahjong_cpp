#ifndef UI_PERSPECTIVE_H_
#define UI_PERSPECTIVE_H_

#include "tiles.h"
#include "Perspective.h"
#include "UIEvent.h"

class MahjongTable;

class Hand;
class Game;

class UserView {
public:
	virtual ~UserView(){};
	virtual UIEvent * popEvent() = 0;
	virtual int getNumberOfPlayer() = 0;
	virtual Hand *getHand(int distance) = 0;
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
	virtual void discard(tile_t tile, int distance);

	virtual void pushActionRequest(PlayerActionRequest *request);

	virtual UIEvent * popEvent();
	virtual int getNumberOfPlayer();
	virtual Hand *getHand(int distance);
	void set_game_flow(MahjongTable * game_flow);

	void setHand(int distance, Hand * hand);

	MahjongTable * getTable();
private:
	void add_event(UIEvent * event);
	void react_after_pick(int distance);
	void react_others_throw(tile_t tile, int distance);

	UIEventQueue eventQueue_;
	tile_t last_tile;
	Hand * Hands[MAX_NUMBER_OF_PLAYER];
	MahjongTable * game_flow;
	UIEventFactory *eventFactory_;
	void _remove_players();
};

#endif /* UI_PERSPECTIVE_H_ */

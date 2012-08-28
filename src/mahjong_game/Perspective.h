#ifndef AGEND_H_
#define AGEND_H_

#include "tile.h"

typedef enum {
	NO_ACTION,
	ACTION_DISCARD,
	ACTION_PICK,
	ACTION_PONG,
	ACTION_CHOW,
	ACTION_KONG,
	ACTION_WIN,
	ACTION_RESTART
}action_t;

class PlayerActionRequest {
public:
	PlayerActionRequest(action_t action, tile_t tile, int a) : action_(action), tile_(tile){}

public:
	action_t action_;
	tile_t tile_;
};

class Perspective {
public:
	Perspective() : currentActionRequest_(NULL){}
	virtual ~Perspective(){}
	virtual void deal(tile_t tiles[], int n, int distance)=0;
	virtual void pick(tile_t tile, int distance)=0;
	virtual void pong(tile_t tile, int distance)=0;
	virtual int chow(tile_t tile, tile_t with, int distance)=0;
	virtual void win(int score, int distance)=0;
	virtual action_t popActionRequest(tile_t* tile)=0;
	virtual PlayerActionRequest * popActionRequest(){return NULL;}
	virtual void set_action(PlayerActionRequest *actionRequest)=0;
	virtual void discard_tile(tile_t tile, int distance)=0;
protected:
	PlayerActionRequest * currentActionRequest_;
};

#endif /* AGEND_H_ */

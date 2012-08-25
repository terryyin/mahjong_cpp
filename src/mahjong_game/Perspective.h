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

class Perspective {
public:
	virtual ~Perspective(){}
	virtual void deal(tile_t tiles[], int n, int distance)=0;
	virtual void pick(tile_t tile, int distance)=0;
	virtual void pong(tile_t tile, int distance)=0;
	virtual int chow(tile_t tile, tile_t with, int distance)=0;
	virtual void win(int score, int distance)=0;
	virtual action_t get_action(tile_t* tile)=0;
	virtual void set_action(action_t action, tile_t tile)=0;
	virtual void discard_tile(tile_t tile, int distance)=0;

};

#endif /* AGEND_H_ */

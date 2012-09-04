#ifndef AGEND_H_
#define AGEND_H_

#include "tile.h"
#include "PlayerActionRequest.h"

class Perspective {
public:
	Perspective() : currentActionRequest_(NO_ACTION, NO_TILE, 1){}
	virtual ~Perspective(){}

	virtual void deal(tile_t tiles[], int n, int distance)=0;
	virtual void pick(tile_t tile, int distance)=0;
	virtual void pong(tile_t tile, int distance)=0;
	virtual int chow(tile_t tile, tile_t with, int distance)=0;
	virtual void win(int score, int distance)=0;
	virtual void discard(tile_t tile, int distance)=0;

	virtual PlayerActionRequest popActionRequest(){
		PlayerActionRequest saved = currentActionRequest_;
		currentActionRequest_.action_ = NO_ACTION;
		return saved;
	}
	virtual void pushActionRequest(PlayerActionRequest *actionRequest)=0;

protected:
	PlayerActionRequest currentActionRequest_;
};

#endif /* AGEND_H_ */

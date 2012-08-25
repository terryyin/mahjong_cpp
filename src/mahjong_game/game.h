#ifndef SYSTEM_H_
#define SYSTEM_H_


#include "Perspective.h"
class UserPerspective;
class tile_pool_t;
class MahjongTable;
class UserView;

class Game {
public:
	Game();

	virtual ~Game();

	virtual UserView *getUserView();

	virtual void nextMove();

	virtual void setAction(action_t action, tile_t tile);

private:
	tile_pool_t * pool_;
	MahjongTable * table_;
	Perspective * aiPerspective_;
	UserPerspective * userPerspective_;
};

#endif /* SYSTEM_H_ */

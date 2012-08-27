#ifndef SYSTEM_H_
#define SYSTEM_H_


#include "Perspective.h"
class UserPerspective;
class TilePool;
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
	TilePool * pool_;
	MahjongTable * table_;
	Perspective * aiPerspective_;
	UserPerspective * userPerspective_;
};

#endif /* SYSTEM_H_ */

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
	void setTilePool(tile_pool_t* pool);
	virtual UserView *getUserView();
	virtual void update();
	virtual void set_action(action_t action, tile_t tile);

private:
	tile_pool_t * pool_;
	MahjongTable * table_;
	Perspective * aiAgent_;
	UserPerspective * userPerspective_;
};

#endif /* SYSTEM_H_ */

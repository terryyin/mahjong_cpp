#ifndef SYSTEM_H_
#define SYSTEM_H_


#include "Perspective.h"
class UserPerspective;
class Wall;
class MahjongTable;
class UserView;

class Game {
public:
	Game();

	virtual ~Game();

	virtual UserView *getUserView();

	virtual void nextMove(PlayerActionRequest *request);

private:
	Wall * wall_;
	MahjongTable * table_;
	Perspective * aiPerspective_;
	UserPerspective * userPerspective_;
};

#endif /* SYSTEM_H_ */

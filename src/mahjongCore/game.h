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

	void addPlayer(Player * player);

	void tick();

private:
	PlayerActionRequest * popActionRequest();
	Player * getPlayerOfDistance(int i);

private:
	Wall * wall_;
	MahjongTable * table_;
	Player * aiPerspective_;
	Player * player_;
	UserPerspective * userPerspective_;
};

#endif /* SYSTEM_H_ */

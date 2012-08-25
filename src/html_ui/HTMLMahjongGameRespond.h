#ifndef HTMLMAHJONGGAMERESPOND_H_
#define HTMLMAHJONGGAMERESPOND_H_

#include <string>
#include "MahjongGameRespond.h"

class UserView;
class PlayerTiles;

class HTMLMahjongGameRespond : public MahjongGameRespond{
public:
	virtual void newGame(GameID gameID);

	virtual void bye();

	virtual void shutdown();

	virtual void gameDoesNotExist();

	virtual void updateAllHoldings(UserView * view);

	virtual void updateUIEvent(UserView * view);

	const char * getString();

	void clear();

private:
	const char * getTilesArrayString(UserView * view, char buffer[], int buffer_size);
	void catTilesToString(char buffer[], const tile_t * tiles, int n);
	void catEatenToString(char buffer[], const eaten_t * eaten, int n);
	void catPlayerTilesToString(PlayerTiles * player, char buffer[],int buffer_size);
	std::string content_;
};

#endif /* HTMLMAHJONGGAMERESPOND_H_ */

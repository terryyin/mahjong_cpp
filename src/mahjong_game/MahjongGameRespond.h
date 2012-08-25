#ifndef MAHJONGGAMERESPOND_H_
#define MAHJONGGAMERESPOND_H_

#include "HTMLMahjongGameServer.h"
class MahjongGameRespond{
public:
	virtual ~MahjongGameRespond(){}
	virtual void newGame(GameID gameID) = 0;
	virtual void setString(const char *) = 0;
	virtual void bye() = 0;
	virtual void shutdown() = 0;
	virtual void update(HTMLMahjongGameServer* server, GameID gameID) = 0;
	virtual void gameDoesNotExist() = 0;
};
#endif /* MAHJONGGAMERESPOND_H_ */

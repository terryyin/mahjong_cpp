#ifndef HTMLMAHJONGGAMERESPOND_H_
#define HTMLMAHJONGGAMERESPOND_H_

#include <string>

#include "MahjongGameRespond.h"

class HTMLMahjongGameRespond : public MahjongGameRespond{
public:
	HTMLMahjongGameRespond();
	virtual ~HTMLMahjongGameRespond();
	virtual void newGame(GameID gameID);
	virtual void bye();
	virtual void shutdown();
	virtual void update(HTMLMahjongGameServer* server, GameID gameID);
	virtual void gameDoesNotExist();

	const char * getString();
	virtual void setString(const char * string);

private:
	std::string content_;
};

#endif /* HTMLMAHJONGGAMERESPOND_H_ */

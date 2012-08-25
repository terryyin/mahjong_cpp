#ifndef HTMLMAHJONGGAMERESPOND_H_
#define HTMLMAHJONGGAMERESPOND_H_

#include <string>

#include "MahjongGameRespond.h"

class UserView;

class HTMLMahjongGameRespond : public MahjongGameRespond{
public:
	HTMLMahjongGameRespond();
	virtual ~HTMLMahjongGameRespond();
	virtual void newGame(GameID gameID);
	virtual void bye();
	virtual void shutdown();
	virtual void gameDoesNotExist();
	virtual void updateAllHoldings(UserView * view);
	virtual void updateUIEvent(UserView * view);

	const char * getString();
	virtual void setString(const char * string);

private:
	std::string content_;
};

#endif /* HTMLMAHJONGGAMERESPOND_H_ */

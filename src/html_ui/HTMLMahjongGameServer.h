#ifndef HTML_GAME_H_
#define HTML_GAME_H_

#include "Perspective.h"
#include "GameIDMap.h"
class tile_pool_t;
class GameIDMap;
class HTMLCommandParser;

typedef void (*FpShutdownCallback)(void);

class HTMLMahjongGameServer {
public:
	HTMLMahjongGameServer(FpShutdownCallback shutdownCallback = NULL,
			HTMLCommandParser *parser = NULL);

	virtual ~HTMLMahjongGameServer();

	void executeGameCommand(const char * command, const char *parameters,
			char * buffer, int buffer_size);

	virtual GameID startNewGame();

	virtual void killGame(GameID gameID);

	virtual void shutdown();

	virtual Game * getGameByID(GameID);

	GameID getLastGameID();

private:
	GameIDMap *gamePool_;
	HTMLCommandParser *commandParser_;
	FpShutdownCallback shutdownCallback_;
	GameID lastGameID_;
};

#endif /* HTML_GAME_H_ */

#ifndef HTML_GAME_H_
#define HTML_GAME_H_

#include "agent.h"
#include "GameIDMap.h"
class tile_pool_t;
class GameIDMap;
class HTMLCommandParser;

typedef void (*FpShutdownCallback)(void);

class HTMLMahjongGameServer {
public:
	HTMLMahjongGameServer(FpShutdownCallback shutdownCallback = NULL, HTMLCommandParser *parser = NULL);
	virtual ~HTMLMahjongGameServer();
	void executeGameCommand(const char * command, const char *parameters,
			char * buffer, int buffer_size);
	virtual GameID startNewGame();
	virtual void killGame(GameID gameID);
	virtual void shutdown();
	virtual Game * getGameByID(GameID);
	void setPool(GameID playerID, tile_pool_t * pool);
	GameID getLastGameID();

public:
	void show_byebye(char * buffer, int buffer_size);
	void script_to_update_all_holdings(int player_id, char * buffer,
			int buffer_size);
	void generate_ui_event_script(int player_id, char * buffer,
			int buffer_size);

private:
	GameIDMap *gamePool_;
	HTMLCommandParser *commandParser_;
	FpShutdownCallback shutdownCallback_;
	GameID lastGameID_;
};

#endif /* HTML_GAME_H_ */

#ifndef MAHJONGCOMMAND_H_
#define MAHJONGCOMMAND_H_

#include "HTMLMahjongGameServer.h"
class MahjongGameRespond;

class MahjongCommandBase {
public:
	virtual ~MahjongCommandBase() {
	}
	virtual void execute(MahjongGameRespond *respond) =0;
};

class MJCommandStartNew: public MahjongCommandBase {
public:
	MJCommandStartNew(HTMLMahjongGameServer* server);
	virtual ~MJCommandStartNew();
	virtual void execute(MahjongGameRespond *respond);
private:
	HTMLMahjongGameServer* server_;
};

class MJCommandQuitGame: public MahjongCommandBase {
public:
	MJCommandQuitGame(HTMLMahjongGameServer* server, GameID gameID);
	virtual ~MJCommandQuitGame();
	virtual void execute(MahjongGameRespond *respond);
private:
	HTMLMahjongGameServer* server_;
	GameID gameID_;
};

class MJCommandShutdownServer: public MahjongCommandBase {
public:
	MJCommandShutdownServer(HTMLMahjongGameServer* server);
	virtual ~MJCommandShutdownServer();
	virtual void execute(MahjongGameRespond *respond);
private:
	HTMLMahjongGameServer* server_;
};

class MJCommandDoesNotExist: public MahjongCommandBase {
public:
	MJCommandDoesNotExist();
	virtual ~MJCommandDoesNotExist();
	virtual void execute(MahjongGameRespond *respond);
};

class MJCommandAction: public MahjongCommandBase {
public:
	MJCommandAction(HTMLMahjongGameServer* server, Game *game, GameID gameID, action_t action, tile_t tile);
	virtual ~MJCommandAction();
	virtual void execute(MahjongGameRespond *respond);
protected:
	HTMLMahjongGameServer* server_;
	GameID gameID_;
	Game *game_;
	action_t action_;
	tile_t tile_;
};

class MJCommandRestart: public MJCommandAction {
public:
	MJCommandRestart(HTMLMahjongGameServer* server, Game *game, GameID gameID):
		MJCommandAction(server, game, gameID, ACTION_RESTART, NO_TILE){};
};

class MJCommandUpdate : public MJCommandAction {
public:
	MJCommandUpdate(HTMLMahjongGameServer* server, Game *game, GameID gameID):
		MJCommandAction(server, game, gameID, NO_ACTION, NO_TILE){};
	virtual void execute(MahjongGameRespond *respond);
};
class MJCommandPick: public MJCommandAction {
public:
	MJCommandPick(HTMLMahjongGameServer* server, Game *game, GameID gameID):
		MJCommandAction(server, game, gameID, ACTION_PICK, NO_TILE){};
};
class MJCommandDiscard: public MJCommandAction {
public:
	MJCommandDiscard(HTMLMahjongGameServer* server, Game *game, GameID gameID, tile_t tile):
		MJCommandAction(server, game, gameID, ACTION_DISCARD, tile){};
};
class MJCommandChow: public MJCommandAction {
public:
	MJCommandChow(HTMLMahjongGameServer* server, Game *game, GameID gameID, tile_t tile):
		MJCommandAction(server, game, gameID, ACTION_CHOW, tile){};
};
class MJCommandPong: public MJCommandAction {
public:
	MJCommandPong(HTMLMahjongGameServer* server, Game *game, GameID gameID):
		MJCommandAction(server, game, gameID, ACTION_PONG, NO_TILE){};
};
class MJCommandKong: public MJCommandAction {
public:
	MJCommandKong(HTMLMahjongGameServer* server, Game *game, GameID gameID, tile_t tile):
		MJCommandAction(server, game, gameID, ACTION_KONG, tile){};
};
class MJCommandWin: public MJCommandAction {
public:
	MJCommandWin(HTMLMahjongGameServer* server, Game *game, GameID gameID):
		MJCommandAction(server, game, gameID, ACTION_WIN, NO_TILE){};
};

#endif /* MAHJONGCOMMAND_H_ */

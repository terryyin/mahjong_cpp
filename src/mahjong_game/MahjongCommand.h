#ifndef MAHJONGCOMMAND_H_
#define MAHJONGCOMMAND_H_

#include "HTMLMahjongGameServer.h"
class MahjongGameRespond;

class MahjongCommand {
public:
	virtual ~MahjongCommand() {
	}
	virtual void execute(MahjongGameRespond *respond) =0;
};

class MJCommandStartNew: public MahjongCommand {
public:
	MJCommandStartNew(HTMLMahjongGameServer* server);
	virtual ~MJCommandStartNew();
	virtual void execute(MahjongGameRespond *respond);
private:
	HTMLMahjongGameServer* server_;
};

class MJCommandQuitGame: public MahjongCommand {
public:
	MJCommandQuitGame(HTMLMahjongGameServer* server, GameID gameID);
	virtual ~MJCommandQuitGame();
	virtual void execute(MahjongGameRespond *respond);
private:
	HTMLMahjongGameServer* server_;
	GameID gameID_;
};

class MJCommandShutdownServer: public MahjongCommand {
public:
	MJCommandShutdownServer(HTMLMahjongGameServer* server);
	virtual ~MJCommandShutdownServer();
	virtual void execute(MahjongGameRespond *respond);
private:
	HTMLMahjongGameServer* server_;
};

class MJCommandDoesNotExist: public MahjongCommand {
public:
	MJCommandDoesNotExist();
	virtual ~MJCommandDoesNotExist();
	virtual void execute(MahjongGameRespond *respond);
};

class MJCommandAction: public MahjongCommand {
public:
	MJCommandAction(Game *game, action_t action, tile_t tile);
	virtual ~MJCommandAction();
	virtual void execute(MahjongGameRespond *respond);
protected:
	GameID gameID_;
	Game *game_;
	action_t action_;
	tile_t tile_;
};

class MJCommandRestart: public MJCommandAction {
public:
	MJCommandRestart(Game *game):
		MJCommandAction(game, ACTION_RESTART, NO_TILE){};
};

class MJCommandUpdate : public MJCommandAction {
public:
	MJCommandUpdate(Game *game):
		MJCommandAction(game, NO_ACTION, NO_TILE){};
	virtual void execute(MahjongGameRespond *respond);
};
class MJCommandPick: public MJCommandAction {
public:
	MJCommandPick(Game *game):
		MJCommandAction(game, ACTION_PICK, NO_TILE){};
	virtual void execute(MahjongGameRespond *respond);
};
class MJCommandDiscard: public MJCommandAction {
public:
	MJCommandDiscard(Game *game, tile_t tile):
		MJCommandAction(game, ACTION_DISCARD, tile){};
};
class MJCommandChow: public MJCommandAction {
public:
	MJCommandChow(Game *game, tile_t tile):
		MJCommandAction(game, ACTION_CHOW, tile){};
};
class MJCommandPong: public MJCommandAction {
public:
	MJCommandPong(Game *game):
		MJCommandAction(game, ACTION_PONG, NO_TILE){};
};
class MJCommandKong: public MJCommandAction {
public:
	MJCommandKong(Game *game, tile_t tile):
		MJCommandAction(game, ACTION_KONG, tile){};
};
class MJCommandWin: public MJCommandAction {
public:
	MJCommandWin(Game *game):
		MJCommandAction(game, ACTION_WIN, NO_TILE){};
	virtual void execute(MahjongGameRespond *respond);
};

#endif /* MAHJONGCOMMAND_H_ */

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
	MJCommandStartNew(HTMLMahjongGameServer* server) :
			server_(server) {
	}
	void execute(MahjongGameRespond *respond);
private:
	HTMLMahjongGameServer* server_;
};

class MJCommandQuitGame: public MahjongCommand {
public:
	MJCommandQuitGame(HTMLMahjongGameServer* server, GameID gameID) :
			server_(server), gameID_(gameID) {
	}
	void execute(MahjongGameRespond *respond);
private:
	HTMLMahjongGameServer* server_;
	GameID gameID_;
};

class MJCommandShutdownServer: public MahjongCommand {
public:
	MJCommandShutdownServer(HTMLMahjongGameServer* server):
		server_(server) {}
	void execute(MahjongGameRespond *respond);
private:
	HTMLMahjongGameServer* server_;
};

class MJCommandDoesNotExist: public MahjongCommand {
public:
	void execute(MahjongGameRespond *respond);
};

class MJCommandAction: public MahjongCommand {
public:
	MJCommandAction(Game *game, action_t action, tile_t tile) :
			game_(game), action_(action), tile_(tile) {
	}
	void execute(MahjongGameRespond *respond);
protected:
	Game *game_;
	action_t action_;
	tile_t tile_;
};

class MJCommandRestart: public MJCommandAction {
public:
	MJCommandRestart(Game *game) :
			MJCommandAction(game, ACTION_RESTART, NO_TILE) {
	}
};

class MJCommandPick: public MJCommandAction {
public:
	MJCommandPick(Game *game) :
			MJCommandAction(game, ACTION_PICK, NO_TILE) {
	}
};

class MJCommandDiscard: public MJCommandAction {
public:
	MJCommandDiscard(Game *game, tile_t tile) :
			MJCommandAction(game, ACTION_DISCARD, tile) {
	}
};

class MJCommandChow: public MJCommandAction {
public:
	MJCommandChow(Game *game, tile_t tile) :
			MJCommandAction(game, ACTION_CHOW, tile) {
	}
};

class MJCommandPong: public MJCommandAction {
public:
	MJCommandPong(Game *game) :
			MJCommandAction(game, ACTION_PONG, NO_TILE) {
	}
};

class MJCommandKong: public MJCommandAction {
public:
	MJCommandKong(Game *game, tile_t tile) :
			MJCommandAction(game, ACTION_KONG, tile) {
	}
};

class MJCommandWin: public MJCommandAction {
public:
	MJCommandWin(Game *game) :
			MJCommandAction(game, ACTION_WIN, NO_TILE) {
	}
};

#endif /* MAHJONGCOMMAND_H_ */

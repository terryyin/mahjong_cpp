#include "MahjongCommand.h"
#include "mahjong_game.h"
#include "HTMLMahjongGameServer.h"
#include "HTMLMahjongGameRespond.h"

MJCommandStartNew::MJCommandStartNew(HTMLMahjongGameServer * server) :
		server_(server) {
}

MJCommandStartNew::~MJCommandStartNew() {
}

void MJCommandStartNew::execute(MahjongGameRespond *respond) {
	int gameID = server_->startNewGame();
	respond->newGame(gameID);
}

MJCommandQuitGame::MJCommandQuitGame(HTMLMahjongGameServer * server,
		GameID gameID) :
		server_(server), gameID_(gameID) {
}

MJCommandQuitGame::~MJCommandQuitGame() {
}

void MJCommandQuitGame::execute(MahjongGameRespond *respond) {
	server_->killGame(gameID_);
	respond->bye();
}

MJCommandShutdownServer::MJCommandShutdownServer(HTMLMahjongGameServer * server) :
		server_(server) {
}

MJCommandShutdownServer::~MJCommandShutdownServer() {
}

void MJCommandShutdownServer::execute(MahjongGameRespond *respond) {
	server_->shutdown();
	respond->shutdown();
}

MJCommandAction::MJCommandAction(HTMLMahjongGameServer * server, Game * game, GameID gameID, action_t action, tile_t tile) :
		server_(server), gameID_(gameID), game_(game), action_(action), tile_(tile) {
}

MJCommandAction::~MJCommandAction() {
}

void MJCommandAction::execute(MahjongGameRespond *respond) {
	game_->update();
	game_->set_action(action_, tile_);
	respond->update(server_, gameID_);
}

MJCommandDoesNotExist::MJCommandDoesNotExist() {
}

MJCommandDoesNotExist::~MJCommandDoesNotExist() {
}

void MJCommandDoesNotExist::execute(MahjongGameRespond *respond) {
	respond->gameDoesNotExist();
}

void MJCommandUpdate::execute(MahjongGameRespond *respond) {
	respond->update(server_, gameID_);
}


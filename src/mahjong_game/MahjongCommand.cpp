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

MJCommandAction::MJCommandAction(Game * game, action_t action, tile_t tile) :
		game_(game), action_(action), tile_(tile) {
}

MJCommandAction::~MJCommandAction() {
}

void MJCommandAction::execute(MahjongGameRespond *respond) {
	game_->setAction(action_, tile_);
	game_->nextMove();
	UserView * view = game_->getUserView();
	respond->updateAllHoldings(view);
	respond->updateUIEvent(view);
}

MJCommandDoesNotExist::MJCommandDoesNotExist() {
}

MJCommandDoesNotExist::~MJCommandDoesNotExist() {
}

void MJCommandDoesNotExist::execute(MahjongGameRespond *respond) {
	respond->gameDoesNotExist();
}

void MJCommandUpdate::execute(MahjongGameRespond *respond) {
	game_->nextMove();
	UserView * view = game_->getUserView();
	respond->updateAllHoldings(view);
	respond->updateUIEvent(view);
}

void MJCommandPick::execute(MahjongGameRespond *respond) {
	game_->setAction(action_, tile_);
	game_->nextMove();
	game_->nextMove();
	respond->updateUIEvent(game_->getUserView());
}

void MJCommandWin::execute(MahjongGameRespond *respond) {
	game_->setAction(action_, tile_);
	game_->nextMove();
	respond->updateUIEvent(game_->getUserView());
}


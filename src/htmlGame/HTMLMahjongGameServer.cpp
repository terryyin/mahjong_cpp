#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mahjong_game.h"
#include "HTMLMahjongGameServer.h"
#include "MahjongCommand.h"
#include "HTMLCommandParser.h"
#include "HTMLMahjongGameRespond.h"

HTMLMahjongGameServer::HTMLMahjongGameServer(
		FpShutdownCallback shutdownCallback, HTMLCommandParser *parser) :
		shutdownCallback_(shutdownCallback), lastGameID_(0) {
	gamePool_ = new GameIDMap();
	commandParser_ = parser;
	if (commandParser_ == NULL)
		commandParser_ = new HTMLCommandParser(this);
}

HTMLMahjongGameServer::~HTMLMahjongGameServer() {
	delete gamePool_;
	delete commandParser_;
}

GameID HTMLMahjongGameServer::startNewGame() {
	Game * game = new Game;
	lastGameID_ = gamePool_->addGameAndGetID(game);
	return lastGameID_;
}

void HTMLMahjongGameServer::killGame(GameID gameID) {
	gamePool_->removeAndDeleteGame(gameID);
}

void HTMLMahjongGameServer::executeGameCommand(const char * command,
		const char *parameters, HTMLMahjongGameRespond *respond) {
	MahjongCommand * mjCommand = commandParser_->parse(command, parameters);
	mjCommand->execute(respond);
	delete mjCommand;
}

void HTMLMahjongGameServer::shutdown() {
	if (shutdownCallback_ != NULL)
		shutdownCallback_();
}

GameID HTMLMahjongGameServer::getLastGameID() {
	return lastGameID_;
}

Game * HTMLMahjongGameServer::getGameByID(GameID gameID) {
	return gamePool_->getGameByID(gameID);
}

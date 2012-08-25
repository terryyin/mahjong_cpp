#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mahjong_game.h"
#include "HTMLMahjongGameServer.h"
#include "agent.h"
#include "ui_agent.h"
#include "mj_table.h"
#include "GameIDMap.h"
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

static void do_user_do_not_exist_error(char * buffer, int buffer_size) {
	snprintf(buffer, buffer_size,
			"alert('Game does not exist. Restart, please.');");
}

void HTMLMahjongGameServer::script_to_update_all_holdings(int player_id,
		char * buffer, int buffer_size) {
	Game * game = gamePool_->getGameByID(player_id);
	if (!game) {
		do_user_do_not_exist_error(buffer, buffer_size);
		return;
	}
	char tmp[1024] = "";
	game->getUIAgent()->get_tiles_array_string(tmp, 1024);
	snprintf(buffer, buffer_size, "App.UpdateHolding(%s);", tmp);

}

void HTMLMahjongGameServer::generate_ui_event_script(int player_id,
		char * buffer, int buffer_size) {
	Game * game = gamePool_->getGameByID(player_id);
	if (!game) {
		do_user_do_not_exist_error(buffer, buffer_size);
		return;
	}

	game->getUIAgent()->update_game();
	script_to_update_all_holdings(player_id, buffer, buffer_size);
	ui_event_t event;
	char tmp[1024];
	while (game->getUIAgent()->pop_event(&event)) {
		switch (event.event) {
		case UI_EVENT_DISCARD:
			sprintf(tmp, "App.Throw(%d, %d);", event.tiles[0],
					event.player_distance_to_me_clockwise);
			if (1 == event.player_distance_to_me_clockwise)
				strcat(tmp, "App.StopUpdate();");
			else
				strcat(tmp, "App.ResumeUpdate();");

			break;
		case UI_EVENT_WIN:
			sprintf(tmp, "App.WinAck(%d, %d);", 0, event.score);
			break;
		case UI_EVENT_PICK:
			sprintf(tmp, "App.Pick(%d, %d);",
					event.player_distance_to_me_clockwise, event.tiles[0]);
			if (0 == event.player_distance_to_me_clockwise)
				strcat(tmp, "App.StopUpdate();");
			else
				strcat(tmp, "App.ResumeUpdate();");
			break;
		case UI_EVENT_MESSAGE:
			sprintf(tmp, "alert(\"%s\");", event.message);
			break;
		case UI_EVENT_CHOW_ABLE:
			sprintf(tmp, "App.LightButton('chow');");
			break;
		case UI_EVENT_PONG_ABLE:
			sprintf(tmp, "App.LightButton('pong');");
			break;
		case UI_EVENT_WIN_ABLE:
			sprintf(tmp, "App.LightButton('win');");
			break;
		default:
			sprintf(tmp, "'invalid event%d';", event.event);
			break;
		}

		strcat(buffer, tmp);
	}
}

void HTMLMahjongGameServer::killGame(GameID gameID) {
	gamePool_->removeAndDeleteGame(gameID);
}

void HTMLMahjongGameServer::show_byebye(char * buffer, int buffer_size) {
	shutdown();
	snprintf(buffer, buffer_size, "<HTML><BODY>Bye!</BODY></HTML>");

}

void HTMLMahjongGameServer::executeGameCommand(const char * command,
		const char *parameters, char * buffer, int buffer_size) {
	HTMLMahjongGameRespond respond;

	MahjongCommandBase * mjCommand = commandParser_->parse(command, parameters);
	mjCommand->execute(&respond);
	strncpy(buffer, respond.getString(), buffer_size);
	delete mjCommand;
}

void HTMLMahjongGameServer::setPool(GameID playerID, tile_pool_t * pool) {
	Game * game = gamePool_->getGameByID(playerID);
	game->getUIAgent()->getTable()->setPool(pool);
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

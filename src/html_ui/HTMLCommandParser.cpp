#include "HTMLCommandParser.h"
#include "MahjongCommand.h"
#include "mahjong_game.h"
HTMLCommandParser::HTMLCommandParser(HTMLMahjongGameServer * server) :
		server_(server) {
}
HTMLCommandParser::~HTMLCommandParser() {
}
void HTMLCommandParser::parse_parameter(const char* parameters, GameID& gameID,
		tile_t& tile) {
	if (parameters != NULL && parameters[0] >= '0' && parameters[0] <= '9') {
		int param = atoi(parameters);
		gameID = param / 1000;
		tile = param % 1000;
	}
}

MahjongCommandBase * HTMLCommandParser::parse(const char * command,
		const char *parameters) {
	int gameID = 0;
	tile_t tile = NO_TILE;
	const char * cmd = strchr(command, '/');

	parse_parameter(parameters, gameID, tile);

	if (strcmp(cmd, "/game") == 0)
		return new MJCommandStartNew(server_);

	if (strcmp(cmd, "/bye") == 0)
		return new MJCommandQuitGame(server_, gameID);

	if (strcmp(cmd, "/shutdown") == 0)
		return new MJCommandShutdownServer(server_);

	Game * game = server_->getGameByID(gameID);
	if (game != NULL) {
		if (strcmp(cmd, "/start") == 0)
			return new MJCommandRestart(server_, game, gameID);

		if (strcmp(cmd, "/update") == 0)
			return new MJCommandUpdate(server_, game, gameID);

		if (strcmp(cmd, "/pick") == 0)
			return new MJCommandPick(server_, game, gameID);

		if (strcmp(cmd, "/throw") == 0)
			return new MJCommandDiscard(server_, game, gameID, tile);

		if (strcmp(cmd, "/chow") == 0)
			return new MJCommandChow(server_, game, gameID, tile);

		if (strcmp(cmd, "/pong") == 0)
			return new MJCommandPong(server_, game, gameID);

		if (strcmp(cmd, "/kong") == 0)
			return new MJCommandKong(server_, game, gameID, tile);

		if (strcmp(cmd, "/win") == 0)
			return new MJCommandWin(server_, game, gameID);
	}
	return new MJCommandDoesNotExist;
}

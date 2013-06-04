#include "HTMLCommandParser.h"
#include "MahjongCommand.h"
#include "mahjong_game.h"
#include "string.h"


HTMLCommandParser::HTMLCommandParser(MahjongGameServer * server) :
		server_(server) {
}

HTMLCommandParser::~HTMLCommandParser() {
}

void HTMLCommandParser::parse_parameter(const char* parameters, GameID& gameID,
		Tile& tile) {
	if (parameters != NULL && parameters[0] >= '0' && parameters[0] <= '9') {
		int param = atoi(parameters);
		gameID = param / 1000;
		tile = param % 1000;
	}
}

MahjongCommand * HTMLCommandParser::parse(const char * command,
		const char *parameters) {
	GameID gameID = 0;
	Tile tile = NO_TILE;
	const char * cmd = strchr(command, '/');

	parse_parameter(parameters, gameID, tile);

	return parseWithExtractedParameters(cmd, gameID, tile);
}

MahjongCommand * HTMLCommandParser::parseWithExtractedParameters(
		const char * cmd, GameID gameID, Tile tile) {

	if (strcmp(cmd, "/game") == 0)
		return new MJCommandStartNew(server_);

	if (strcmp(cmd, "/bye") == 0)
		return new MJCommandQuitGame(server_, gameID);

	if (strcmp(cmd, "/shutdown") == 0)
		return new MJCommandShutdownServer(server_);

	Game * game = server_->getGameByID(gameID);
	return parseWithExtractedParametersForGame(game, cmd, tile);
}

MahjongCommand * HTMLCommandParser::parseWithExtractedParametersForGame(
		Game* game, const char * cmd, Tile tile) {
	if (game != NULL) {
		if (strcmp(cmd, "/start") == 0)
			return new MJCommandRestart(game);

		if (strcmp(cmd, "/pick") == 0)
			return new MJCommandPick(game);

		if (strcmp(cmd, "/throw") == 0)
			return new MJCommandDiscard(game, tile);

		if (strcmp(cmd, "/chow") == 0)
			return new MJCommandChow(game, tile);

		if (strcmp(cmd, "/pong") == 0)
			return new MJCommandPong(game);

		if (strcmp(cmd, "/kong") == 0)
			return new MJCommandKong(game, tile);

		if (strcmp(cmd, "/win") == 0)
			return new MJCommandWin(game);
	}
	return new MJCommandDoesNotExist;
}

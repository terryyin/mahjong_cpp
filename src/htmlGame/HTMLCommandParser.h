#ifndef HTMLCOMMANDPARSER_H_
#define HTMLCOMMANDPARSER_H_

#include "mahjong_game.h"
#include "HTMLMahjongGameServer.h"

class MahjongCommand;

class HTMLCommandParser {
public:
	HTMLCommandParser(MahjongGameServer * server = NULL);

	virtual ~HTMLCommandParser();

	virtual MahjongCommand * parse(const char * command,
			const char *parameters);
private:
	MahjongGameServer *server_;
	void parse_parameter(const char* parameters, GameID& gameID, Tile& tile);
	MahjongCommand * parseWithExtractedParameters(const char * cmd,
			GameID gameID, Tile tile);
	MahjongCommand * parseWithExtractedParametersForGame(
			Game* game, const char * cmd, Tile tile);
};

#endif /* HTMLCOMMANDPARSER_H_ */

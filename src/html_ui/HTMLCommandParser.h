/*
 * HTMLCommandParser.h
 *
 *  Created on: Aug 24, 2012
 *      Author: yinterry
 */

#ifndef HTMLCOMMANDPARSER_H_
#define HTMLCOMMANDPARSER_H_

#include "mahjong_game.h"
#include "HTMLMahjongGameServer.h"

class MahjongCommandBase;

class HTMLCommandParser {
public:
	HTMLCommandParser(HTMLMahjongGameServer * server = NULL);
	virtual ~HTMLCommandParser();
	virtual MahjongCommandBase * parse(const char * command,
			const char *parameters);
private:
	HTMLMahjongGameServer *server_;
	void parse_parameter(const char* parameters, GameID& gameID, tile_t& tile);
};

#endif /* HTMLCOMMANDPARSER_H_ */

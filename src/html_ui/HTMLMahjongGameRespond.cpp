#include "HTMLMahjongGameRespond.h"

HTMLMahjongGameRespond::HTMLMahjongGameRespond() {
}

HTMLMahjongGameRespond::~HTMLMahjongGameRespond() {
}

const char * html_frame =
		"<html>\n"
				"<head>\n"
				"<title>Mahjong Game - For Writing Effective Unit Test Training</title> "
				"<script>game_id=%d;</script>\n"
				"<LINK REL=StyleSheet HREF=\"mj.css\" TYPE=\"text/css\">\n"
				"<script src=\"mj.js\" type=\"text/javascript\"></script>\n"
				"</head>\n"
				"<body>\n"
				"</body>\n"
				"</html>\n";

void HTMLMahjongGameRespond::newGame(GameID gameID) {
	const int buffer_size = 1000;
	char buffer[buffer_size];
	snprintf(buffer, buffer_size, html_frame, gameID);
	content_ = buffer;
}

void HTMLMahjongGameRespond::bye() {
}

const char * HTMLMahjongGameRespond::getString() {
	return content_.c_str();
}

void HTMLMahjongGameRespond::setString(const char * string) {
	content_ = string;
}

void HTMLMahjongGameRespond::shutdown() {
	content_ = "<HTML><BODY>shutdown!</BODY></HTML>";
}

void HTMLMahjongGameRespond::update(HTMLMahjongGameServer* server, GameID gameID) {
	const int buffer_size = 1000;
	char buffer[buffer_size];
	server->generate_ui_event_script(gameID, buffer, buffer_size);
	content_ = buffer;
}

void HTMLMahjongGameRespond::gameDoesNotExist() {
	content_ = "alert('Game does not exist. Restart, please.');";
}

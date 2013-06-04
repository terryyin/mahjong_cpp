#ifndef HTMLMAHJONGGAME_H_
#define HTMLMAHJONGGAME_H_

#include "httpd.h"
#include <string>

class MahjongGameServer;
class MahjongGameRespond;
class HTMLMahjongGame: public SimpleHTMLService {
public:
	HTMLMahjongGame(MahjongGameServer *server);
	void callback(const char * command, const char *parameters, char * buffer,
			int buffer_size);
private:
	MahjongGameServer *server_;
	void responseToString(MahjongGameRespond *respond, char * buffer,
			int buffer_size);
};

#endif /* HTMLMAHJONGGAME_H_ */

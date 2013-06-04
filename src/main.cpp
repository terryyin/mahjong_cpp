#include <stdlib.h>
#include <time.h>
#include "httpd.h"
#include "HTMLMahjongGameServer.h"
#include "HTMLMahjongGame.h"
#include "HTMLMahjongGameFactory.h"
#include "string.h"

int main(void)
{
	srand(time(NULL));
	HTMLMahjongGameFactory factory;
	MahjongGameServer server(&factory, set_shutdown_flag);
	HTMLMahjongGame game(&server);
	return server_main(&game);
}

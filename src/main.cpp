#include <stdlib.h>
#include <time.h>
#include "httpd.h"
#include "html_game.h"

static HTMLMahjongGameServer server;
int execute_game_command(const char * command, const char *parameters, char * buffer, int buffer_size)
{
	return server.execute_game_command(command, parameters, buffer, buffer_size);
}

int main(void)
{
	srand(time(NULL));
	game_callback_ptr = execute_game_command;
	server.setShutdownCallback(set_shutdown_flag);
	return server_main();
}

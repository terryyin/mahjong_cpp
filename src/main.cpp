#include <stdlib.h>
#include <time.h>
#include "httpd.h"
#include "HTMLMahjongGameServer.h"

static HTMLMahjongGameServer server(set_shutdown_flag);
void execute_game_command(const char * command, const char *parameters, char * buffer, int buffer_size)
{
	server.executeGameCommand(command, parameters, buffer, buffer_size);
}

int main(void)
{
	srand(time(NULL));
	game_callback_ptr = execute_game_command;
	return server_main();
}

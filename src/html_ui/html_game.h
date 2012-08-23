/*
 * html_game.h
 *
 *  Created on: Feb 7, 2011
 *      Author: terry
 */

#ifndef HTML_GAME_H_
#define HTML_GAME_H_

int execute_game_command(const char * command, const char *parameters, char * buffer, int buffer_size);
extern void (*shutdown_server)(void);
class tile_pool_t;
void setPool(int playerID, tile_pool_t * pool);

#endif /* HTML_GAME_H_ */

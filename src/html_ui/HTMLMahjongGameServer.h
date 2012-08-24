#ifndef HTML_GAME_H_
#define HTML_GAME_H_

#include "agent.h"
class tile_pool_t;
class GameIDMap;
typedef void (*FpShutdownCallback)(void);
class HTMLMahjongGameServer{
public:
	HTMLMahjongGameServer();
	virtual ~HTMLMahjongGameServer();
	int execute_game_command(const char * command, const char *parameters, char * buffer, int buffer_size);
	virtual void shutdown();
	void setPool(int playerID, tile_pool_t * pool);
	void setShutdownCallback(FpShutdownCallback callback);
private:
	void show_byebye(char * buffer, int buffer_size);
	int start_new_player(char * buffer, int buffer_size);
	void script_to_update_all_holdings(int player_id, char * buffer, int buffer_size);
	void generate_ui_event_script(int player_id, char * buffer, int buffer_size);
	void do_action(int player_id, char * buffer, int buffer_size, action_t action, tile_t tile);
	void script_to_bye(int player_id, char * buffer, int buffer_size, action_t action, tile_t tile);
private:
	GameIDMap * gamePool;
	FpShutdownCallback shutdownCallback_;
};

#endif /* HTML_GAME_H_ */

#ifndef UI_AGENT_H_
#define UI_AGENT_H_

#include "tiles.h"
#include "agent.h"
typedef struct user_info_t{

} user_info_t;

typedef enum {
	UI_EVENT_INVALID,
	UI_EVENT_DISCARD,
	UI_EVENT_PICK_ABLE,
	UI_EVENT_PONG_ABLE,
	UI_EVENT_CHOW_ABLE,
	UI_EVENT_WIN_ABLE,
	UI_EVENT_MESSAGE,
	UI_EVENT_WIN,
	UI_EVENT_PICK
}ui_event_name_t;

#define UI_EVENT_MSG_LEN 100
typedef struct {
	ui_event_name_t event;
	int score;
	int player_distance_to_me_clockwise;
	tile_t tiles[MAX_HOLDING_COUNT];
	char message[UI_EVENT_MSG_LEN+1];
} ui_event_t;

class mj_table_t;

#define UI_EVENT_QUEUE_SIZE 10

struct player_t;
class UIAgent: public Agent {
public:
	UIAgent();
	virtual ~UIAgent();
	virtual void deal(tile_t tiles[], int n, int distance);
	virtual void pick(tile_t tile, int distance);
	virtual void pong(tile_t tile, int distance);
	virtual int chow(tile_t tile, tile_t with, int distance);
	virtual void win(int score, int distance);
	virtual action_t get_action(tile_t* tile);
	virtual void set_action(action_t action, tile_t tile);
	virtual void discard_tile(tile_t tile, int distance);

	int pop_event(ui_event_t * output_event);
	const char * get_tiles_array_string(char buffer[], int buffer_size);
	void set_game_flow(mj_table_t * game_flow);
	void update_game();
private:
	void add_event(ui_event_name_t event_name,
			tile_t tiles[], int n, int score, int distance, const char * msg);
	void react_after_pick(int distance);
	void react_others_throw(tile_t tile, int distance);

	ui_event_t event_queue[UI_EVENT_QUEUE_SIZE];
	int event_queue_head;
	int event_queue_tail;
	action_t action;
	tile_t last_tile;
	tile_t action_tile;
	player_t * players[MAX_NUMBER_OF_PLAYER];
	mj_table_t * game_flow;
	void _remove_players();


};
UIAgent * create_ui_agent(void);

#endif /* UI_AGENT_H_ */

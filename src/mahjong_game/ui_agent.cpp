#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ui_agent.h"
#include "player.h"
#include "assert.h"
#include "mj_table.h"

UIAgent::UIAgent() {
	action = NO_ACTION;
	event_queue_head = event_queue_tail = 0;
	game_flow = NULL;
	last_tile = NO_TILE;
	action_tile = NO_TILE;
	int i = 0;
	for (; i < MAX_NUMBER_OF_PLAYER; i++)
		players[i] = NULL;
}

void UIAgent::_remove_players() {
	int i;
	for (i = 0; i < MAX_NUMBER_OF_PLAYER; i++) {
		if (NULL != this->players[i])
			player_destroy(this->players[i]);
		this->players[i] = NULL;
	}
}
UIAgent::~UIAgent() {
	if (this->game_flow) {
		mj_table_t * flow = this->game_flow;
		this->game_flow = NULL;
		mj_table_remove_agent(flow, this);
		mj_table_destroy(flow);
	}
	_remove_players();
}

#define _QUEUE_NEXT_INDEX(i) (i) = (((i)+1)%(UI_EVENT_QUEUE_SIZE))
int UIAgent::pop_event(ui_event_t * output_event) {
	if (this->event_queue_head == this->event_queue_tail)
		return 0;

	ui_event_t * event = &this->event_queue[this->event_queue_head];
	_QUEUE_NEXT_INDEX(this->event_queue_head);
	memcpy(output_event, event, sizeof(ui_event_t));

	return 1;
}

void UIAgent::deal(tile_t tiles[], int n, int distance) {
	player_t * player_data = create_player_data();
	player_deal(player_data, tiles, n);
	assert(MAX_NUMBER_OF_PLAYER > distance && this->players[distance]== NULL);
	this->players[distance] = player_data;
}

void UIAgent::add_event(ui_event_name_t event_name, tile_t tiles[], int n,
		int score, int distance, const char * msg) {
	ui_event_t * event = &this->event_queue[this->event_queue_tail];
	_QUEUE_NEXT_INDEX(this->event_queue_tail);
	if (this->event_queue_tail == this->event_queue_head)
		_QUEUE_NEXT_INDEX(this->event_queue_head);
	event->event = event_name;
	event->score = score;
	event->player_distance_to_me_clockwise = distance;
	memcpy(event->tiles, tiles, n * sizeof(tile_t));
	memset(event->message, 0, sizeof(event->message));
	if (msg) {
		strncpy(event->message, msg, UI_EVENT_MSG_LEN);
	}
}

void UIAgent::react_after_pick(int distance) {
	this->last_tile = NO_TILE;
	if (distance == 0) {
		player_t * player = this->players[0];
		if (player_is_able_to_win(player, NO_TILE))
			add_event(UI_EVENT_WIN_ABLE, NULL, 0, 0, 0, NULL);
	}
}
void UIAgent::pick(tile_t tile, int distance) {
	player_t * player_data = this->players[distance];
	assert(player_data);
	player_pick(player_data, tile);

	add_event(UI_EVENT_PICK, &tile, 1, 0, distance, NULL);

	react_after_pick(distance);
}
void UIAgent::pong(tile_t tile, int distance) {
	player_t * player_data = this->players[distance];
	assert(player_data);
	player_pong(player_data, tile);
	this->action = NO_ACTION;
	react_after_pick(distance);
}

int UIAgent::chow(tile_t tile, tile_t with, int distance) {
	player_t * player_data = this->players[distance];
	assert(player_data);
	if (!player_chow(player_data, tile, with))
		return 0;
	this->action = NO_ACTION;
	react_after_pick(distance);
	return 1;
}

void UIAgent::win(int score, int distance) {
	add_event(UI_EVENT_WIN, NULL, 0, score, distance, NULL);
}
action_t UIAgent::get_action(tile_t* tile) {
	if (tile != NULL)
		*tile = this->action_tile;
	return this->action;
}

void UIAgent::set_action(action_t action, tile_t tile) {
	player_t *player = this->players[0];
	if (action == ACTION_WIN) {
		if (!player_is_able_to_win(player, this->last_tile)) {
			add_event(UI_EVENT_MESSAGE, NULL, 0, 0, 0, "Are you kidding?");
			return;
		}
	} else if (action == ACTION_PONG) {
		if (!player_is_able_to_pong(player, this->last_tile)) {
			add_event(UI_EVENT_MESSAGE, NULL, 0, 0, 0, "Are you kidding?");
			return;
		}
	} else if (action == ACTION_CHOW) {
		if (!player_is_able_to_chew(player, this->last_tile)) {
			add_event(UI_EVENT_MESSAGE, NULL, 0, 0, 0, "Are you kidding?");
			return;
		}
	}
	this->action = action;
	this->action_tile = tile;
	if (action == ACTION_RESTART)
		_remove_players();
}

void cat_tiles_to_string(char buffer[], const tile_t * tiles, int n) {
	char tmp_tile[100];
	int i = 0;
	for (i = 0; i < n; i++) {
		sprintf(tmp_tile, "%d,", tiles[i]);
		strcat(buffer, tmp_tile);
	}
}
void cat_eaten_to_string(char buffer[], const eaten_t * eaten, int n) {
	char tmp_tile[100];
	int i = 0;
	for (i = 0; i < n; i++) {
		sprintf(tmp_tile, "%d,", eaten[i]);
		strcat(buffer, tmp_tile);
	}
}

void player_tiles_to_string(player_t * player, char buffer[], int buffer_size) {
	strcat(buffer, "[");
	tile_t tiles[MAX_HOLDING_COUNT];
	eaten_t eaten[MAX_EATEN_COUNT];
	int n = player_get_holdings(player, tiles, MAX_HOLDING_COUNT);
	cat_tiles_to_string(buffer, tiles, n);
	tiles[0] = player_get_current(player);
	cat_tiles_to_string(buffer, tiles, 1);
	n = player_get_eaten(player, eaten, MAX_EATEN_COUNT);
	cat_eaten_to_string(buffer, eaten, n);
	int len = strlen(buffer);
	if (buffer[len - 1] == ',') {
		buffer[len - 1] = '\0';
	}
	strcat(buffer, "]");
}
const char * UIAgent::get_tiles_array_string(char buffer[], int buffer_size) {
	sprintf(buffer, "[");
	int i;
	for (i = 0; i < MAX_NUMBER_OF_PLAYER; i++) {
		if (this->players[i] != NULL) {
			if (i)
				strcat(buffer, ",");
			player_tiles_to_string(this->players[i], buffer, buffer_size);
		}
	}
	strcat(buffer, "]");
	return buffer;
}

void UIAgent::react_others_throw(tile_t tile, int distance) {
	if (distance != 0) {
		player_t * player = this->players[0];
		if (player_is_able_to_win(player, tile))
			add_event(UI_EVENT_WIN_ABLE, NULL, 0, 0, 0, NULL);
		if (player_is_able_to_pong(player, tile))
			add_event(UI_EVENT_PONG_ABLE, NULL, 0, 0, 0, NULL);
		if (distance == 1) {
			if (player_is_able_to_chew(player, tile))
				add_event(UI_EVENT_CHOW_ABLE, NULL, 0, 0, 0, NULL);
		}
	}
}
void UIAgent::discard_tile(tile_t tile, int distance) {
	this->last_tile = tile;
	player_t * player_data = this->players[distance];
	if (player_data != NULL)
		player_discard_tile(player_data, tile);

	add_event(UI_EVENT_DISCARD, &tile, 1, 0, distance, NULL);

	react_others_throw(tile, distance);
}

void UIAgent::set_game_flow(struct mj_table_t * game_flow) {
	this->game_flow = game_flow;
}
void UIAgent::update_game() {
	mj_table_update_state(this->game_flow);
}

UIAgent * create_ui_agent(void) {
	return new UIAgent();
}

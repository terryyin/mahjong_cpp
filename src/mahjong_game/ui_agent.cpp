#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ui_agent.h"
#include "player.h"
#include "assert.h"
#include "mj_table.h"
#include "game.h"

UIAgent::UIAgent() {
	action = NO_ACTION;
	event_queue_head = event_queue_tail = 0;
	game_flow = NULL;
	game = NULL;
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
			delete this->players[i];
		this->players[i] = NULL;
	}
}
UIAgent::~UIAgent() {
	if (this->game_flow)
		this->game_flow->remove_agent(this);
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
	PlayerData * player_data = create_player_data();
	player_data->deal(tiles, n);
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
		PlayerData * player = this->players[0];
		if (player->is_able_to_win(NO_TILE))
			add_event(UI_EVENT_WIN_ABLE, NULL, 0, 0, 0, NULL);
	}
}
void UIAgent::pick(tile_t tile, int distance) {
	PlayerData * player_data = this->players[distance];
	assert(player_data);
	player_data->pick(tile);

	add_event(UI_EVENT_PICK, &tile, 1, 0, distance, NULL);

	react_after_pick(distance);
}
void UIAgent::pong(tile_t tile, int distance) {
	PlayerData * player_data = this->players[distance];
	assert(player_data);
	player_data->pong(tile);
	this->action = NO_ACTION;
	react_after_pick(distance);
}

int UIAgent::chow(tile_t tile, tile_t with, int distance) {
	PlayerData * player_data = this->players[distance];
	assert(player_data);
	if (!player_data->chow(tile, with))
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
	PlayerData *player = this->players[0];
	if (action == ACTION_WIN) {
		if (!player->is_able_to_win(this->last_tile)) {
			add_event(UI_EVENT_MESSAGE, NULL, 0, 0, 0, "Are you kidding?");
			return;
		}
	} else if (action == ACTION_PONG) {
		if (!player->is_able_to_pong(this->last_tile)) {
			add_event(UI_EVENT_MESSAGE, NULL, 0, 0, 0, "Are you kidding?");
			return;
		}
	} else if (action == ACTION_CHOW) {
		if (!player->is_able_to_chew(this->last_tile)) {
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

void player_tiles_to_string(PlayerData * player, char buffer[], int buffer_size) {
	strcat(buffer, "[");
	tile_t tiles[MAX_HOLDING_COUNT];
	eaten_t eaten[MAX_EATEN_COUNT];
	int n = player->get_holdings(tiles, MAX_HOLDING_COUNT);
	cat_tiles_to_string(buffer, tiles, n);
	tiles[0] = player->get_current();
	cat_tiles_to_string(buffer, tiles, 1);
	n = player->get_eaten(eaten, MAX_EATEN_COUNT);
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
		PlayerData * player = this->players[0];
		if (player->is_able_to_win(tile))
			add_event(UI_EVENT_WIN_ABLE, NULL, 0, 0, 0, NULL);
		if (player->is_able_to_pong(tile))
			add_event(UI_EVENT_PONG_ABLE, NULL, 0, 0, 0, NULL);
		if (distance == 1) {
			if (player->is_able_to_chew(tile))
				add_event(UI_EVENT_CHOW_ABLE, NULL, 0, 0, 0, NULL);
		}
	}
}
void UIAgent::discard_tile(tile_t tile, int distance) {
	this->last_tile = tile;
	PlayerData * player_data = this->players[distance];
	if (player_data != NULL)
		player_data->discard_tile(tile);

	add_event(UI_EVENT_DISCARD, &tile, 1, 0, distance, NULL);

	react_others_throw(tile, distance);
}

void UIAgent::set_game_flow(MahjongTable * game_flow) {
	this->game_flow = game_flow;
}

MahjongTable * UIAgent::getTable()
{
	return this->game_flow;
}


void UIAgent::set_game(Game * game) {
	this->game = game;
}

void UIAgent::update_game() {
	this->game_flow->update_state();
}

UIAgent * create_ui_agent(void) {
	return new UIAgent();
}

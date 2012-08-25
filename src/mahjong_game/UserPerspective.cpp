#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UserPerspective.h"
#include "PlayerTiles.h"
#include "assert.h"
#include "mj_table.h"
#include "game.h"

UserPerspective::UserPerspective() {
	action = NO_ACTION;
	game_flow = NULL;
	game = NULL;
	last_tile = NO_TILE;
	action_tile = NO_TILE;
	int i = 0;
	for (; i < MAX_NUMBER_OF_PLAYER; i++)
		players[i] = NULL;
}

void UserPerspective::_remove_players() {
	int i;
	for (i = 0; i < MAX_NUMBER_OF_PLAYER; i++) {
		if (NULL != this->players[i])
			delete this->players[i];
		this->players[i] = NULL;
	}
}
UserPerspective::~UserPerspective() {
	_remove_players();
}

UIEvent * UserPerspective::popEvent() {
	return eventQueue_.popEvent();
}

void UserPerspective::deal(tile_t tiles[], int n, int distance) {
	PlayerTiles * player_data = create_player_data();
	player_data->deal(tiles, n);
	assert(MAX_NUMBER_OF_PLAYER > distance && this->players[distance]== NULL);
	this->players[distance] = player_data;
}

void UserPerspective::add_event(UIEvent * event) {
	eventQueue_.addEvent(event);
}

void UserPerspective::react_after_pick(int distance) {
	this->last_tile = NO_TILE;
	if (distance == 0) {
		PlayerTiles * player = this->players[0];
		if (player->is_able_to_win(NO_TILE))
			add_event(eventFactory_.createEnableWinEvent());
	}
}
void UserPerspective::pick(tile_t tile, int distance) {
	PlayerTiles * player_data = this->players[distance];
	assert(player_data);
	player_data->pick(tile);

	add_event(eventFactory_.createPickEvent(tile, distance));

	react_after_pick(distance);
}
void UserPerspective::pong(tile_t tile, int distance) {
	PlayerTiles * player_data = this->players[distance];
	assert(player_data);
	player_data->pong(tile);
	this->action = NO_ACTION;
	react_after_pick(distance);
}

int UserPerspective::chow(tile_t tile, tile_t with, int distance) {
	PlayerTiles * player_data = this->players[distance];
	assert(player_data);
	if (!player_data->chow(tile, with))
		return 0;
	this->action = NO_ACTION;
	react_after_pick(distance);
	return 1;
}

void UserPerspective::win(int score, int distance) {
	add_event(eventFactory_.createWinEvent(distance, score));
}
action_t UserPerspective::get_action(tile_t* tile) {
	if (tile != NULL)
		*tile = this->action_tile;
	return this->action;
}

void UserPerspective::set_action(action_t action, tile_t tile) {
	PlayerTiles *player = this->players[0];
	if (action == ACTION_WIN) {
		if (!player->is_able_to_win(this->last_tile)) {
			add_event(eventFactory_.createMessageEvent("Are you kidding?"));
			return;
		}
	} else if (action == ACTION_PONG) {
		if (!player->is_able_to_pong(this->last_tile)) {
			add_event(eventFactory_.createMessageEvent("Are you kidding?"));
			return;
		}
	} else if (action == ACTION_CHOW) {
		if (!player->is_able_to_chew(this->last_tile)) {
			add_event(eventFactory_.createMessageEvent("Are you kidding?"));
			return;
		}
	}
	this->action = action;
	this->action_tile = tile;
	if (action == ACTION_RESTART)
		_remove_players();
}

void UserPerspective::react_others_throw(tile_t tile, int distance) {
	if (distance != 0) {
		PlayerTiles * player = this->players[0];
		if (player->is_able_to_win(tile))
			add_event(eventFactory_.createEnableWinEvent());
		if (player->is_able_to_pong(tile))
			add_event(eventFactory_.createEnablePongEvent());
		if (distance == 1) {
			if (player->is_able_to_chew(tile))
				add_event(eventFactory_.createEnableChewEvent());
		}
	}
}
void UserPerspective::discard_tile(tile_t tile, int distance) {
	this->last_tile = tile;
	PlayerTiles * player_data = this->players[distance];
	if (player_data != NULL)
		player_data->discard_tile(tile);

	add_event(eventFactory_.createDiscardEvent(tile, distance));

	react_others_throw(tile, distance);
}

void UserPerspective::set_game_flow(MahjongTable * game_flow) {
	this->game_flow = game_flow;
}

MahjongTable * UserPerspective::getTable()
{
	return this->game_flow;
}


void UserPerspective::set_game(Game * game) {
	this->game = game;
}

void UserPerspective::update_game() {
	this->game_flow->nextMove();
}

int UserPerspective::getNumberOfPlayer() {
	int count = 0;
	for (int i = 0; i < MAX_NUMBER_OF_PLAYER; i++)
		if (this->players[i] != NULL)
			count++;
	return count;
}

PlayerTiles *UserPerspective::getPlayerData(int distance) {
	return this->players[distance];
}


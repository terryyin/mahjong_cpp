#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ai_agent.h"
#include "player.h"
#include "evaluator.h"
#include "assert.h"

AIAgent::AIAgent() {
	action = ACTION_RESTART;
	player = NULL;
	evaluator = create_evaluator_r();
}
AIAgent::~AIAgent() {
	if (player)
		player_destroy(player);
	delete evaluator;
}

void AIAgent::deal(tile_t tiles[], int n, int distance) {
	if (distance == 0) {
		player_t * player_data = create_player_data();
		player_deal(player_data, tiles, n);
		player = player_data;
	}
}

tile_t AIAgent::ai_which_to_discard() {
	int i;
	int max = 0;
	int index_to_throw = 0;
	tile_t holdings[MAX_HOLDING_COUNT + 1];
	tile_t tiles[MAX_HOLDING_COUNT + 1];
	int tile_count = player_get_holdings(player, holdings, MAX_HOLDING_COUNT);
	holdings[tile_count] = player_get_current(player);
	for (i = 0; i < tile_count + 1; i++) {
		player_get_holdings(player, tiles, MAX_HOLDING_COUNT);
		tiles[i] = player_get_current(player);
		int score = evaluator->evaluate_array(tiles, tile_count);
		if (score > max) {
			max = score;
			index_to_throw = i;
		}
	}

	return holdings[index_to_throw];
}
void AIAgent::pick(tile_t tile, int distance) {
	if (distance == 0) {
		player_pick(player, tile);
		if (player_is_able_to_win(player, NO_TILE))
			action = ACTION_WIN;
		else {
			action = ACTION_DISCARD;
			this->tile = ai_which_to_discard();
		}
	}
}

void AIAgent::pong(tile_t tile, int distance) {
}
int AIAgent::chow(tile_t tile, tile_t with, int distance) {
	return 0;
}
void AIAgent::win(int score, int distance) {
	action = ACTION_RESTART;
	player_destroy(player);
	player = NULL;
}

action_t AIAgent::get_action(tile_t* tile) {
	if (tile != NULL)
		*tile = this->tile;
	return action;
}

void AIAgent::set_action(action_t action, tile_t tile) {

	this->action = action;
	this->tile = tile;
}

void AIAgent::discard_tile(tile_t tile, int distance) {
	if (distance == 0)
		player_discard_tile(player, tile);
	else {
		if (player_is_able_to_win(player, tile))
			action = ACTION_WIN;
		else
			action = ACTION_PICK;
	}
}

void AIAgent::setEvaluator(Evaluator * evaluator){
	if (this->evaluator != NULL)
		delete this->evaluator;
	this->evaluator = evaluator;
}

AIAgent * create_ai_agent() {
	return new AIAgent();
}


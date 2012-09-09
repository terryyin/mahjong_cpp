#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AIPerspective.h"
#include "Hand.h"
#include "EvaluatorAdaptor.h"
#include "assert.h"

AIPerspective::AIPerspective() {
	currentActionRequest_.action_ = ACTION_RESTART;
	player = NULL;
	evaluator = createEvaluatorAdaptor();
}
AIPerspective::~AIPerspective() {
	if (player)
		delete player;
	delete evaluator;
}

void AIPerspective::deal(tile_t tiles[], int n, int distance) {
	if (distance == 0) {
		Hand * player_data = createHand();
		player_data->deal(tiles, n);
		player = player_data;
	}
}

tile_t AIPerspective::whichToDiscard() {
	int i;
	int max = 0;
	int index_to_throw = 0;
	tile_t holdings[MAX_HOLDING_COUNT + 1];
	tile_t tiles[MAX_HOLDING_COUNT + 1];
	int tile_count = player->getHoldings(holdings, MAX_HOLDING_COUNT);
	holdings[tile_count] = player->getCurrentTileAtHand();
	for (i = 0; i < tile_count + 1; i++) {
		player->getHoldings(tiles, MAX_HOLDING_COUNT);
		tiles[i] = player->getCurrentTileAtHand();
		int score = evaluator->evaluate_array(tiles, tile_count);
		if (score > max) {
			max = score;
			index_to_throw = i;
		}
	}

	return holdings[index_to_throw];
}
void AIPerspective::pick(tile_t tile, int distance) {
	if (distance == 0) {
		player->pick(tile);
		if (player->isAbleToWin(NO_TILE))
			currentActionRequest_.action_ = ACTION_WIN;
		else {
			currentActionRequest_.action_ = ACTION_DISCARD;
			currentActionRequest_.tile_ = whichToDiscard();
		}
	}
}

void AIPerspective::pong(tile_t tile, int distance) {
}

int AIPerspective::chow(tile_t tile, tile_t with, int distance) {
	return 0;
}

void AIPerspective::win(int score, int distance) {
	currentActionRequest_.action_ = ACTION_RESTART;
	delete player;
	player = NULL;
}

void AIPerspective::pushActionRequest(PlayerActionRequest *actionRequest) {

}

void AIPerspective::discard(tile_t tile, int distance) {
	if (distance == 0)
		player->discard_tile(tile);
	else {
		if (player->isAbleToWin(tile))
			currentActionRequest_.action_ = ACTION_WIN;
		else
			currentActionRequest_.action_ = ACTION_PICK;
	}
}

void AIPerspective::setEvaluator(EvaluatorAdaptor * evaluator){
	if (this->evaluator != NULL)
		delete this->evaluator;
	this->evaluator = evaluator;
}


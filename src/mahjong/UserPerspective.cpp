#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UserPerspective.h"
#include "Hand.h"
#include "assert.h"
#include "mj_table.h"
#include "game.h"
#include "HTMLUIEvent.h"

UserPerspective::UserPerspective(UIEventFactory *eventFactory) {
	if (eventFactory == NULL)
		eventFactory = new HTMLEventFactory;
	eventFactory_ = eventFactory;
	game_flow = NULL;
	last_tile = NO_TILE;
	int i = 0;
	for (; i < MAX_NUMBER_OF_PLAYER; i++)
		Hands[i] = NULL;
}

void UserPerspective::_remove_players() {
	for (int i = 0; i < MAX_NUMBER_OF_PLAYER; i++) {
		if (NULL != this->Hands[i])
			delete this->Hands[i];
		this->Hands[i] = NULL;
	}
}
UserPerspective::~UserPerspective() {
	_remove_players();
	delete eventFactory_;
}

UIEvent * UserPerspective::popEvent() {
	return eventQueue_.popEvent();
}

void UserPerspective::deal(tile_t tiles[], int n, int distance) {
	currentActionRequest_.action_ = NO_ACTION;
	Hand * player_data = createHand();
	player_data->deal(tiles, n);
	delete Hands[distance];
	this->Hands[distance] = player_data;
	if (distance == 0)
		add_event(eventFactory_->createDealEvent(this));
}

void UserPerspective::add_event(UIEvent * event) {
	eventQueue_.addEvent(event);
}

void UserPerspective::react_after_pick(int distance) {
	this->last_tile = NO_TILE;
	if (distance == 0) {
		Hand * player = this->Hands[0];
		if (player->isAbleToWin(NO_TILE))
			add_event(eventFactory_->createEnableWinEvent());
	}
}
void UserPerspective::pick(tile_t tile, int distance) {
	Hand * player_data = this->Hands[distance];
	assert(player_data);
	player_data->pick(tile);

	add_event(eventFactory_->createPickEvent(tile, distance));

	react_after_pick(distance);
}
void UserPerspective::pong(tile_t tile, int distance) {
	Hand * player_data = this->Hands[distance];
	assert(player_data);
	player_data->pong(tile);
	add_event(eventFactory_->createDealEvent(this));

	react_after_pick(distance);
}

int UserPerspective::chow(tile_t tile, tile_t with, int distance) {
	Hand * player_data = this->Hands[distance];
	assert(player_data);
	if (!player_data->chow(tile, with)) {
		if (distance == 0)
			add_event(eventFactory_->createMessageEvent("Cannot meld chow."));
		return 0;
	}
	add_event(eventFactory_->createDealEvent(this));
	react_after_pick(distance);
	return 1;
}

void UserPerspective::win(int score, int distance) {
	add_event(eventFactory_->createWinEvent(distance, score));
}

void UserPerspective::pushActionRequest(PlayerActionRequest * actionRequest) {
	Hand *player = this->Hands[0];
	if (actionRequest->action_ == ACTION_WIN) {
		if (!player->isAbleToWin(this->last_tile)) {
			add_event(eventFactory_->createMessageEvent("Are you kidding?"));
			return;
		}
	} else if (actionRequest->action_ == ACTION_PONG) {
		if (!player->isAbleToPong(this->last_tile)) {
			add_event(eventFactory_->createMessageEvent("Are you kidding?"));
			return;
		}
	} else if (actionRequest->action_ == ACTION_CHOW) {
		if (!player->isAbleToChow(this->last_tile)) {
			add_event(eventFactory_->createMessageEvent("Are you kidding?"));
			return;
		}
	}
	this->currentActionRequest_ = *actionRequest;
}

void UserPerspective::react_others_throw(tile_t tile, int distance) {
	if (distance != 0) {
		Hand * player = this->Hands[0];
		if (player->isAbleToWin(tile))
			add_event(eventFactory_->createEnableWinEvent());
		if (player->isAbleToPong(tile))
			add_event(eventFactory_->createEnablePongEvent());
		if (distance == 1) {
			if (player->isAbleToChow(tile))
				add_event(eventFactory_->createEnableChewEvent());
		}
	}
}
void UserPerspective::discard(tile_t tile, int distance) {
	this->last_tile = tile;
	Hand * player_data = this->Hands[distance];
	if (player_data != NULL)
		player_data->discard_tile(tile);

	add_event(eventFactory_->createDiscardEvent(tile, distance));

	react_others_throw(tile, distance);
}

void UserPerspective::set_game_flow(MahjongTable * game_flow) {
	this->game_flow = game_flow;
}

MahjongTable * UserPerspective::getTable()
{
	return this->game_flow;
}


int UserPerspective::getNumberOfPlayer() {
	int count = 0;
	for (int i = 0; i < MAX_NUMBER_OF_PLAYER; i++)
		if (this->Hands[i] != NULL)
			count++;
	return count;
}

Hand *UserPerspective::getHand(int distance) {
	return this->Hands[distance];
}

void UserPerspective::setHand(int distance, Hand * hand) {
	delete this->Hands[distance];
	this->Hands[distance] = hand;
}


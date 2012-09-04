#include "Perspective.h"
#include "Wall.h"
#include "mj_table.h"

MahjongTable::MahjongTable(Wall *wall) :
		wall_(wall), player_count_(0), current_player(0), host(0), restartCount_(
				0), currentState_(&endOfGameState_), endOfGameState_(this), pickedState_(
				this), pickingState_(this) {
}

MahjongTable::~MahjongTable() {
}

Perspective * MahjongTable::getPlayerOfDistance(int i) {
	return this->players[(this->current_player + i) % this->player_count_];
}

void MahjongTable::addPlayer(Perspective * player) {
	this->players[this->player_count_++] = player;
}

int MahjongTable::getPlayerCount() {
	return this->player_count_;
}

void MahjongTable::pick(tile_t tile) {
	int i = 0;
	for (i = 0; i < this->player_count_; i++) {
		Perspective * perspective = getPlayerOfDistance(i);
		perspective->pick(tile, i);
	}
}

void MahjongTable::changeHost() {
	this->host = (this->host + 1) % this->player_count_;
	this->current_player = this->host;
}

void MahjongTable::changeCurrentPlayer(int distance) {
	this->current_player = (this->current_player + distance)
			% this->player_count_;
}

void MahjongTable::win(int score) {
	int i = 0;
	for (i = 0; i < this->player_count_; i++) {
		Perspective * perspective = getPlayerOfDistance(i);
		perspective->win(score, i);
	}
	changeHost();
}

void MahjongTable::deal(tile_t tiles[], int n) {
	int i = 0;
	for (i = 0; i < this->player_count_; i++) {
		Perspective * perspective = getPlayerOfDistance(i);
		perspective->deal(tiles, n, i);
	}
	changeCurrentPlayer(1);
}

void MahjongTable::throw_tile(tile_t tile) {
	int i = 0;
	for (i = 0; i < this->player_count_; i++) {
		Perspective * perspective = getPlayerOfDistance(i);
		perspective->discard(tile, i);
	}
	this->last_tile = tile;
	changeCurrentPlayer(1);
}

void MahjongTable::pong() {
	int i = 0;
	for (i = 0; i < this->player_count_; i++) {
		Perspective * perspective = getPlayerOfDistance(i);
		perspective->pong(this->last_tile, i);
	}
}

int MahjongTable::chow(tile_t with) {
	Perspective * perspective = getPlayerOfDistance(0);
	if (!perspective->chow(last_tile, with, 0))
		return 0;
	for (int i = 1; i < player_count_; i++) {
		perspective = getPlayerOfDistance(i);
		perspective->chow(last_tile, with, i);
	}
	return 1;
}

void MahjongTable::restartGame() {
	wall_->shuffleAndRebuild();
	tile_t tiles[MAX_HOLDING_COUNT];
	int cnt = getPlayerCount();
	for (; cnt > 0; cnt--) {
		for (int i = 0; i < MAX_HOLDING_COUNT; i++) {
			tiles[i] = wall_->popATile();
		}
		deal(tiles, MAX_HOLDING_COUNT);
	}
	pick(wall_->popATile());
	currentState_ = &pickedState_;
}

void MahjongTable::restartGameWhenAllPlayersAreReady() {
	changeCurrentPlayer(1);
	if (++restartCount_ == player_count_) {
		restartCount_ = 0;
		restartGame();
	}
}

void MahjongTable::discard(tile_t& action_tile) {
	throw_tile(action_tile);
	if (wall_->isEnd()) {
		win(0);
		currentState_ = &endOfGameState_;
	} else {
		currentState_ = &pickingState_;
	}
}

void MahjongTable::doWin() {
	win(1);
	currentState_ = &endOfGameState_;
}

void MahjongTable::doPick() {
	pick(wall_->popATile());
	currentState_ = &pickedState_;
}

void MahjongTable::doPong() {
	pong();
	currentState_ = &pickedState_;
}

void MahjongTable::doChow(tile_t action_tile) {
	if (chow(action_tile)) {
		currentState_ = &pickedState_;
	}
}

PlayerActionRequest MahjongTable::popActionRequest() {
	Perspective* perspective = getPlayerOfDistance(0);
	return perspective->popActionRequest();
}

void MahjongTable::nextMove() {
	while (true) {
		PlayerActionRequest actionRequest = popActionRequest();
		if (!actionRequest.hasAction())
			break;
		actionRequest.doPlayerAction(currentState_);
	}
}

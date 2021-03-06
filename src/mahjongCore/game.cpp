#include "game.h"
#include "Wall.h"
#include "mj_table.h"
#include "UserPerspective.h"
#include "AIPerspective.h"

Game::Game() {
	wall_ = createWall();
	table_ = new MahjongTable(wall_);
	aiPerspective_ = new AIPerspective();
	userPerspective_ = new UserPerspective();
	table_->addPlayer(userPerspective_);
	table_->addPlayer(aiPerspective_);
	player_ = NULL;
}

Game::~Game() {
	delete wall_;
	delete table_;
	delete userPerspective_;
	delete aiPerspective_;
	delete player_;
}

void Game::addPlayer(Player * player) {
	player_ = player;
}

UserView *Game::getUserView() {
	return userPerspective_;
}

void Game::nextMove(PlayerActionRequest *request){
	userPerspective_->pushActionRequest(request);
	table_->nextMove();
}

Player * Game::getPlayerOfDistance(int i) {
	UNUSED(i);
	return player_;
}

PlayerActionRequest * Game::popActionRequest() {
	Player* perspective = getPlayerOfDistance(0);
	return perspective->takeActionRequest1();
}

void Game::tick() {
	while (true) {
		PlayerActionRequest *actionRequest = popActionRequest();
		if (!actionRequest->hasAction())
			break;
		actionRequest->doPlayerAction(NULL);
	}
}

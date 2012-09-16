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
}

Game::~Game() {
	delete wall_;
	delete table_;
	delete userPerspective_;
	delete aiPerspective_;
}

UserView *Game::getUserView() {
	return userPerspective_;
}

void Game::nextMove(PlayerActionRequest *request){
	userPerspective_->pushActionRequest(request);
	table_->nextMove();
}


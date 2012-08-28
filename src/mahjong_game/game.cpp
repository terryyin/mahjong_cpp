#include "game.h"
#include "TilePool.h"
#include "mj_table.h"
#include "PlayerTiles.h"
#include "UserPerspective.h"
#include "AIPerspective.h"

Game::Game() {
	pool_ = create_tile_pool();
	table_ = new MahjongTable(pool_);
	aiPerspective_ = new AIPerspective();
	userPerspective_ = new UserPerspective();
	userPerspective_->set_game_flow(table_);
	userPerspective_->set_game(this);
	table_->addPlayer(userPerspective_);
	table_->addPlayer(aiPerspective_);
}

Game::~Game() {
	delete pool_;
	delete table_;
	delete userPerspective_;
	delete aiPerspective_;
}

UserView *Game::getUserView() {
	return userPerspective_;
}

void Game::nextMove(){
	table_->nextMove();
}

void Game::setAction(PlayerActionRequest * actionRequest) {
	userPerspective_->set_action(actionRequest);
}


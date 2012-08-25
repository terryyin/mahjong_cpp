#include "game.h"
#include "tile_pool.h"
#include "mj_table.h"
#include "player.h"
#include "UserPerspective.h"
#include "AIPerspective.h"

Game::Game() {
	pool_ = create_tile_pool();
	table_ = create_mj_table(pool_);
	aiAgent_ = create_ai_agent();
	userPerspective_ = createUserPerspective();
	userPerspective_->set_game_flow(table_);
	userPerspective_->set_game(this);
	table_->add_player(userPerspective_);
	table_->add_player(aiAgent_);
}
Game::~Game() {
	delete pool_;
	delete table_;
}

void Game::setTilePool(tile_pool_t* pool){
	table_->setPool(pool);
}

UserView *Game::getUserView() {
	return userPerspective_;
}

void Game::update(){
	table_->update_state();
}

void Game::set_action(action_t action, tile_t tile) {
	userPerspective_->set_action(action, tile);
}

#include "game.h"
#include "tile_pool.h"
#include "mj_table.h"
#include "player.h"
#include "ui_agent.h"
#include "ai_agent.h"

Game::Game() {
	pool = create_tile_pool();
	table = create_mj_table(pool);
	ai_agent = create_ai_agent();
	agent = create_ui_agent();
	agent->set_game_flow(table);
	agent->set_game(this);
	table->add_player(agent);
	table->add_player(ai_agent);
}
Game::~Game() {
	delete pool;
	delete table;
}

void Game::setTilePool(tile_pool_t* pool){
	this->pool = pool;
}

UIAgent *Game::getUIAgent() {
	return agent;
}

void Game::update(){
	table->update_state();
}

void Game::set_action(action_t action, tile_t tile) {
	agent->set_action(action, tile);
}

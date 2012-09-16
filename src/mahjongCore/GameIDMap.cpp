#include "game.h"
#include "GameIDMap.h"

using namespace std;

GameIDMap::GameIDMap() {
	id_counter_ = 1;
}

GameIDMap::~GameIDMap() {
	map<int, Game*>::iterator it;
	for (it = gameMap_.begin(); it != gameMap_.end(); it++)
		delete it->second;
}

GameID GameIDMap::addGameAndGetID(Game * game) {
	gameMap_.insert(std::pair<int, Game *>(id_counter_, game));
	return id_counter_++;
}

Game * GameIDMap::getGameByID(GameID id) {
	return gameMap_[id];
}

void GameIDMap::removeAndDeleteGame(GameID id) {
	delete gameMap_[id];
	gameMap_.erase(id);
}

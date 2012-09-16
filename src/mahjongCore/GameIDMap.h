#ifndef GAMEIDMAP_H_
#define GAMEIDMAP_H_
#include <map>
class Game;

typedef int GameID;

class GameIDMap {
public:
	GameIDMap();

	~GameIDMap();

	GameID addGameAndGetID(Game * ui);

	Game * getGameByID(GameID id);

	void removeAndDeleteGame(GameID id);

private:
	int id_counter_;
	std::map<int, Game *> gameMap_;
};

#endif /* GAMEIDMAP_H_ */

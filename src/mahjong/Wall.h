#ifndef GAME__H
#define GAME__H

#include "tiles.h"

#define MAX_TILE_COUNT 500

class Wall {
public:
	Wall(const tile_t * tileTypes, int tileTypeCount, int maxPicks);
	virtual ~Wall();
	virtual void shuffleAndRebuild();
	virtual bool isEnd();
	virtual tile_t popATile();

private:
	void initializePool();
	void swap(int index1, int index2);
	int getAllCount();
	int randomIndex();

private:
	tile_t tilePool_[MAX_TILE_COUNT];
	const tile_t *tileTypes_;
	int tileTypeCount_;
	int picksCount_;
	int maxPicks_;
};

extern Wall * (*createWall)(void);

#endif

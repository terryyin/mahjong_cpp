#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Wall.h"

TEST_GROUP(wall) {
	Wall * wall;
	int maxPops;
	void setup() {
		wall = NULL;
		maxPops = 2;
	}
	void teardown() {
		delete wall;
	}
};

TEST(wall, wallIsNotEndWhenCreated) {
	Tile tileTypes[] = {C(1)};
	wall = new Wall(tileTypes, 1, maxPops);
	CHECK(!wall->isEnd());
}

TEST(wall, popFromwallThatIsNotEnd) {
	Tile tileTypes[] = {C(1)};
	wall = new Wall(tileTypes, 1, maxPops);
	CHECK_EQUAL(C(1), wall->popATile());
}

TEST(wall, wallBecomesEmptyWhenPopTheMaxTimes) {
	Tile tileTypes[] = {C(1)};
	int maxPops = 2;
	wall = new Wall(tileTypes, 1, maxPops);
	wall->popATile();
	wall->popATile();
	CHECK(wall->isEnd());
}

TEST(wall, popRightTilesAfterShuffle) {
	Tile tileTypes[] = {C(1), C(2)};
	int maxPops = 8;
	wall = new Wall(tileTypes, 2, maxPops);

	wall->shuffleAndRebuild();

	while (!wall->isEnd()) {
		Tile tile = wall->popATile();
		CHECK(tile == C(1) || tile == C(2));
	}
}

TEST(wall, randomnessAfterShuffle) {
	// use the same seed to
	// get the same set of random number every time.
	srand(100);

	Tile tileTypes[] = {C(1), C(2)};
	int maxPops = 8;
	wall = new Wall(tileTypes, 2, maxPops);

	wall->shuffleAndRebuild();

	bool hasC1 = false, hasC2 = false;
	for(int i = 0; i < 4; i++) {
		Tile tile = wall->popATile();
		hasC1 |= (tile == C(1));
		hasC2 |=(tile == C(2));
	}

	CHECK(hasC1);
	CHECK(hasC2);
}


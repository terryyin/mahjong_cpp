#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "TilePool.h"

TEST_BASE(base_tile_pool) {
	TilePool * game;
	void setup() {
		game = create_tile_pool();
	}
	void teardown() {
		delete game;
	}
};

TEST_GROUP_BASE(tile_pool, base_tile_pool)
{};

TEST(tile_pool, not_end)
{
	LONGS_EQUAL(0, game->is_end());
}

TEST(tile_pool, end)
{
	for (int i = 0; i < MAX_PICKS-1; i++) {
		game->pop_a_tile();
		LONGS_EQUAL(0, game->is_end());
	}

	game->pop_a_tile();
	LONGS_EQUAL(1, game->is_end());
}

TEST_GROUP_BASE(tile_pool_shuffle, base_tile_pool)
{
	tile_t all[ALL_COUNT];
	void setup() {
		base_tile_pool::setup();
		shuffle_and_get_all_tiles();
	}
	void shuffle_and_get_all_tiles (){
		srand(100);
		int cnt = 0;
		game->shuffle();
		while (ALL_COUNT > cnt) all[cnt++] = game->pop_a_tile();
	}
	double average_of_array(tile_t tiles[], int from, int count) {
		double sum = 0;
		for (int i = from; i < from + count; i++)
			sum += tiles[i];
		return sum / count;
	}
};

TEST(tile_pool_shuffle, check_sum_of_shuffle)
{
	int checksum = 0;
	for (int i = 0; i < ALL_COUNT; i++) checksum+=all[i];
//	LONGS_EQUAL(11304, checksum);
}


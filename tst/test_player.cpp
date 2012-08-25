#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tiles.h"
#include "PlayerTiles.h"
#include "mj_table.h"
#include "mocks.h"

TEST_GROUP(common_player) {
	PlayerTiles * player;
	tile_t tiles[100];
	void setup() {
		player=create_player_data();

	}
	void teardown() {
		delete player;
	}
};

TEST(common_player,get_tiles_when_not_dealt) {
	tile_t tiles[14];
	LONGS_EQUAL(0, player->get_holdings(tiles, 14));
	LONGS_EQUAL(NO_TILE, player->get_current());
}

TEST(common_player,get_tiles_when_dealt) {
	tile_t tiles_of_deal[4] = {C(3), C(4), C(1), C(2)};
	tile_t tiles[14];
	player->deal(tiles_of_deal, 4);
	LONGS_EQUAL(4, player->get_holdings(tiles, 14));
	LONGS_EQUAL(C(1), tiles[0]);
	LONGS_EQUAL(C(4), tiles[3]);
	LONGS_EQUAL(NO_TILE, player->get_current());
}
TEST(common_player,eaten_info_has_been_reset_after_deal) {
	eaten_t eaten;
	tile_t tiles_of_deal[] = {C(3)};
	player->pong(C(1));
	player->deal(tiles_of_deal, 1);
	LONGS_EQUAL(0, player->get_eaten(&eaten, 1));
}

TEST(common_player,is_able_to_pong) {
	tile_t tiles1[] = {MJ_EAST, MJ_EAST};
	player->deal(tiles1, 2);
	LONGS_EQUAL(1, player->is_able_to_pong(MJ_EAST));
	tile_t tiles2[] = {MJ_EAST, MJ_NORTH, MJ_NORTH, MJ_NORTH};
	player->deal(tiles2, 4);
	LONGS_EQUAL(0, player->is_able_to_pong(MJ_EAST));
}

TEST(common_player,pong) {
	tile_t tiles1[] = {MJ_EAST, MJ_EAST, MJ_NORTH};
	eaten_t eaten[3];
	player->deal(tiles1, 3);
	player->pong(MJ_EAST);
	LONGS_EQUAL(0,player->get_holdings(tiles, 3));
	LONGS_EQUAL(1,player->get_eaten(eaten, 3));
	LONGS_EQUAL(PONG(MJ_EAST), eaten[0]);
}
TEST(common_player,chow_fail) {
	tile_t tiles1[] = {1, 2, 3};
	eaten_t eaten[3];
	player->deal(tiles1, 3);
	LONGS_EQUAL(0, player->chow(4, 3));
	LONGS_EQUAL(3,player->get_holdings(tiles, 3));
	LONGS_EQUAL(0,player->get_eaten(eaten, 3));
}
TEST(common_player,chow_middle) {
	tile_t tiles1[] = {1, 3};
	eaten_t eaten[3];
	player->deal(tiles1, 2);
	LONGS_EQUAL(1, player->chow(2, 1));
	LONGS_EQUAL(0,player->get_holdings(tiles, 3));
	LONGS_EQUAL(1,player->get_eaten(eaten, 3));
	LONGS_EQUAL(CHOW(1), eaten[0]);
}

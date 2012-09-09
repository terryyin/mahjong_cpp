#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tiles.h"
#include "Hand.h"
#include "mj_table.h"
#include "mocks.h"

TEST_GROUP(Hand) {
	Hand * player;
	tile_t tiles[100];
	void setup() {
		player=createHand();

	}
	void teardown() {
		delete player;
	}
};

TEST(Hand,get_tiles_when_not_dealt) {
	tile_t tiles[14];
	LONGS_EQUAL(0, player->getHoldings(tiles, 14));
	LONGS_EQUAL(NO_TILE, player->getCurrentTileAtHand());
}

TEST(Hand,get_tiles_when_dealt) {
	tile_t tiles_of_deal[4] = {C(3), C(4), C(1), C(2)};
	tile_t tiles[14];
	player->deal(tiles_of_deal, 4);
	LONGS_EQUAL(4, player->getHoldings(tiles, 14));
	LONGS_EQUAL(C(1), tiles[0]);
	LONGS_EQUAL(C(4), tiles[3]);
	LONGS_EQUAL(NO_TILE, player->getCurrentTileAtHand());
}
TEST(Hand,meld_info_has_been_reset_after_deal) {
	meld_t meld;
	tile_t tiles_of_deal[] = {C(3)};
	player->pong(C(1));
	player->deal(tiles_of_deal, 1);
	LONGS_EQUAL(0, player->getMelds(&meld, 1));
}

TEST(Hand,isAbleToPong) {
	tile_t tiles1[] = {MJ_EAST, MJ_EAST};
	player->deal(tiles1, 2);
	LONGS_EQUAL(1, player->isAbleToPong(MJ_EAST));
	tile_t tiles2[] = {MJ_EAST, MJ_NORTH, MJ_NORTH, MJ_NORTH};
	player->deal(tiles2, 4);
	LONGS_EQUAL(0, player->isAbleToPong(MJ_EAST));
}

TEST(Hand,pong) {
	tile_t tiles1[] = {MJ_EAST, MJ_EAST, MJ_NORTH};
	meld_t meld[3];
	player->deal(tiles1, 3);
	player->pong(MJ_EAST);
	LONGS_EQUAL(0,player->getHoldings(tiles, 3));
	LONGS_EQUAL(1,player->getMelds(meld, 3));
	LONGS_EQUAL(PONG(MJ_EAST), meld[0]);
}
TEST(Hand,chow_fail) {
	tile_t tiles1[] = {1, 2, 3};
	meld_t meld[3];
	player->deal(tiles1, 3);
	LONGS_EQUAL(0, player->chow(4, 3));
	LONGS_EQUAL(3,player->getHoldings(tiles, 3));
	LONGS_EQUAL(0,player->getMelds(meld, 3));
}
TEST(Hand,chow_middle) {
	tile_t tiles1[] = {1, 3};
	meld_t meld[3];
	player->deal(tiles1, 2);
	LONGS_EQUAL(1, player->chow(2, 1));
	LONGS_EQUAL(0,player->getHoldings(tiles, 3));
	LONGS_EQUAL(1,player->getMelds(meld, 3));
	LONGS_EQUAL(CHOW(1), meld[0]);
}

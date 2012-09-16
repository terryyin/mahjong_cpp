#include "CppUTest/TestHarness.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TileArray.h"

const int tile_array_size = 14;
TEST_GROUP(tiles_array) {
	Tile tile_array[tile_array_size];
	void setup() {
		for (int i = 0; i < tile_array_size; i++)
			tile_array[i] = NO_TILE;
	}
};

TEST(tiles_array, not_winning_when_empty) {
	TileArray tileArray(tile_array, 0);
	CHECK(!tileArray.winWith(NO_TILE));
}

TEST(tiles_array, NOT_winning_when_one_tile_left) {
	tile_array[0] = MJ_CHARACTOR(1);
	TileArray tileArray(tile_array, 1);
	CHECK(!tileArray.winWith(NO_TILE));
}

TEST(tiles_array, winning_when_a_pair) {
	tile_array[0] = MJ_CHARACTOR(1);
	TileArray tileArray(tile_array, 1);
	CHECK(tileArray.winWith(MJ_CHARACTOR(1)));
}

TEST(tiles_array, not_winning_when_2_different) {
	tile_array[0] = MJ_CHARACTOR(1);
	TileArray tileArray(tile_array, 1);
	CHECK(!tileArray.winWith(MJ_CHARACTOR(2)));
}

TEST(tiles_array, not_winning_when__3_different) {
	tile_array[0] = MJ_CHARACTOR(2);
	tile_array[1] = MJ_CHARACTOR(5);
	TileArray tileArray(tile_array, 2);
	CHECK(!tileArray.winWith(MJ_CHARACTOR(8)));
}
TEST(tiles_array, not_winning_when__a_pair_and_one) {
	tile_array[0] = MJ_CHARACTOR(2);
	tile_array[1] = MJ_CHARACTOR(2);
	TileArray tileArray(tile_array, 2);
	CHECK(!tileArray.winWith(MJ_CHARACTOR(8)));
}
TEST(tiles_array, winning_when_a_pong) {
	tile_array[0] = MJ_CHARACTOR(1);
	tile_array[1] = MJ_CHARACTOR(1);
	TileArray tileArray(tile_array, 2);
	CHECK(tileArray.winWith(MJ_CHARACTOR(1)));
}

TEST(tiles_array, not_winning_when_4) {
	tile_array[0] = MJ_CHARACTOR(1);
	tile_array[1] = MJ_CHARACTOR(1);
	tile_array[2] = MJ_CHARACTOR(1);
	TileArray tileArray(tile_array, 3);
	CHECK(!tileArray.winWith(MJ_CHARACTOR(8)));
}

TEST(tiles_array, winning_when_a_pong_and_a_pair) {
	tile_array[0] = MJ_CHARACTOR(1);
	tile_array[1] = MJ_CHARACTOR(1);
	tile_array[2] = MJ_CHARACTOR(1);
	tile_array[3] = MJ_CHARACTOR(8);
	TileArray tileArray(tile_array, 4);
	CHECK(tileArray.winWith(MJ_CHARACTOR(8)));
}

TEST(tiles_array, winning_when_a_pair_and_a_pong) {
	tile_array[0] = MJ_CHARACTOR(1);
	tile_array[1] = MJ_CHARACTOR(1);
	tile_array[2] = MJ_CHARACTOR(8);
	tile_array[3] = MJ_CHARACTOR(8);
	TileArray tileArray(tile_array, 4);
	CHECK(tileArray.winWith(MJ_CHARACTOR(8)));
}

TEST(tiles_array, winning_when_a_a_chew) {
	tile_array[0] = MJ_CHARACTOR(1);
	tile_array[1] = MJ_CHARACTOR(2);
	TileArray tileArray(tile_array, 2);
	CHECK(tileArray.winWith(MJ_CHARACTOR(3)));
}

TEST(tiles_array, winning_when_a_a_chew_and_a_pair_within) {
	tile_array[0] = MJ_CHARACTOR(1);
	tile_array[1] = MJ_CHARACTOR(2);
	tile_array[2] = MJ_CHARACTOR(2);
	tile_array[3] = MJ_CHARACTOR(2);
	TileArray tileArray(tile_array, 4);
	CHECK(tileArray.winWith(MJ_CHARACTOR(3)));
}

TEST(tiles_array, winning_when_a_a_chew_and_a_pair_and_a_pong) {
	tile_array[0] = MJ_CHARACTOR(1);
	tile_array[1] = MJ_CHARACTOR(1);
	tile_array[2] = MJ_CHARACTOR(1);
	tile_array[3] = MJ_CHARACTOR(2);
	tile_array[4] = MJ_CHARACTOR(2);
	tile_array[5] = MJ_CHARACTOR(2);
	tile_array[6] = MJ_CHARACTOR(2);
	TileArray tileArray(tile_array, 7);
	CHECK(tileArray.winWith(MJ_CHARACTOR(3)));
}

TEST(tiles_array, not_winning_when_2_pairs) {
	tile_array[0] = MJ_CHARACTOR(1);
	tile_array[1] = MJ_CHARACTOR(1);
	tile_array[2] = MJ_CHARACTOR(3);

	TileArray tileArray(tile_array, 3);
	CHECK(!tileArray.winWith(MJ_CHARACTOR(3)));
}

TEST(tiles_array, a_winning_case) {
	Tile t[] = { C(2), C(3), C(4), R(2), R(2), R(6), R(7), B(2), B(2), B(2),
			B(7), B(8), B(9) };
	TileArray tileArray(t, 13);
	CHECK(tileArray.winWith(R(5)));
}

TEST(tiles_array, replacingOneOfTwoOccurances) {
	Tile t[] = { C(2), C(2)};
	TileArray tileArray(t, 2);
	tileArray.replaceOneOf(C(2), C(1));
	CHECK_EQUAL(C(1), tileArray[0]);
	CHECK_EQUAL(C(2), tileArray[1]);
}


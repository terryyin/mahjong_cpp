#include "CppUTest/TestHarness.h"
#include "tile.h"

TEST_GROUP(tile)
{
};

TEST(tile, sameTilesShouldBeEqual) {
	Tile tile1 = MJ_EAST;
	Tile tile2 = MJ_EAST;
	CHECK_EQUAL(tile1, tile2);
}

TEST(tile, subtracting) {
	CHECK_EQUAL(2, B(3) - B(1));
}

TEST(tile, stringConverterShouldConvertToTileFaceName) {
	STRCMP_EQUAL("C(1)", C(1));
}

TEST(tile, stringConverterShouldConvertToTileFaceNameC2) {
	STRCMP_EQUAL("C(2)", C(2));
}

TEST(tile, undefinedTileShouldConvertToUndefinedString) {
	STRCMP_EQUAL("undef", Tile(MJ_EAST.getID()+1));
}


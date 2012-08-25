#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "HTMLMahjongGameRespond.h"

TEST_GROUP(HTMLMahjongGameRespond) {
	HTMLMahjongGameRespond respond;
};

TEST(HTMLMahjongGameRespond, new_game){
	respond.newGame(123);
	const char * resp = respond.getString();
	CHECK(strstr(resp, "<script>game_id=123;</script>"));
}

TEST(HTMLMahjongGameRespond, bye){
	respond.bye();
	const char * resp = respond.getString();
	STRCMP_EQUAL("", resp);
}

TEST(HTMLMahjongGameRespond, shutdown){
	respond.shutdown();
	const char * resp = respond.getString();
	CHECK(strstr(resp, "shutdown"));
}
TEST(HTMLMahjongGameRespond, game_does_not_exist){
	respond.gameDoesNotExist();
	const char * resp = respond.getString();
	STRCMP_EQUAL("alert('Game does not exist. Restart, please.');", resp);
}

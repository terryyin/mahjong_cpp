#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "HTMLMahjongGameServer.h"
#include "tile_pool.h"
#include "evaluator.h"

Evaluator * create_simple_evaluator_r();
void set_cheapest_tile(tile_t tile);

#include "mocks.h"

class EverIncreasingTilePool: public tile_pool_t {
public:
	EverIncreasingTilePool() :
			current_tile_(1), tile_pool_end_(false) {
	}

	tile_t pop_a_tile() {
		return current_tile_++;
	}

	int is_end() {
		return tile_pool_end_;
	}

	void empty() {
		tile_pool_end_ = true;
	}

	void setCurrentTile(int t) {
		current_tile_ = t;
	}
private:
	tile_t current_tile_;
	bool tile_pool_end_;
} *lastCreatedEverIncreasingTilePool = NULL;

static tile_pool_t * createEverIncreasingTilePool() {
	lastCreatedEverIncreasingTilePool = new EverIncreasingTilePool;
	return lastCreatedEverIncreasingTilePool;
}


#define HAS_STRING(expect, actual) HAS_STRING_LOCATION(expect, actual, __FILE__, __LINE__)
TEST_GROUP(html_game) {

	int gameID;
	HTMLMahjongGameServer server;
	HTMLMahjongGameRespond respond;
	EverIncreasingTilePool *tilePool;

	void setup() {
		UT_PTR_SET(create_evaluator_r, create_simple_evaluator_r);
		UT_PTR_SET(create_tile_pool, createEverIncreasingTilePool);
		server.executeGameCommand("/game", "", &respond);
		gameID = server.getLastGameID();
		tilePool = lastCreatedEverIncreasingTilePool;
	}

	void teardown() {
	}

	char * idtoa(int id, int tile) {
		static char temp[10];
		sprintf(temp, "%d", id * 1000 + tile);
		return temp;
	}

	void execute_cmd(const char * cmd, int tile) {
		respond.clear();
		server.executeGameCommand(cmd, idtoa(gameID, tile), &respond);
	}

	void HAS_STRING_LOCATION(const char * expect, const char * actual,
			const char * filename, int line) {
		if (strstr(actual, expect) == NULL) {
			const int buffer_size = 500;
			char text[buffer_size];
			snprintf(text, buffer_size - 1, "The actual string <%s>\n"
					"does not include the expected string <%s>", actual,
					expect);
			FAIL_LOCATION(text, filename, line);
		}
	}
};

TEST(html_game, start) {
	execute_cmd("/start", 0);
	STRCMP_EQUAL("App.Pick(0, 27);App.UpdateHolding([[1,2,3,4,5,6,7,8,9,10,11,12,13,27],[14,15,16,17,18,19,20,21,22,23,24,25,26,0]]);"
	, respond.getString());
}

TEST(html_game, a_game) {
	execute_cmd("/start", 0);
	execute_cmd("/throw", 1);
	STRCMP_EQUAL("App.Throw(1, 0);|App.Pick(1, 28);|App.Throw(14, 1);", respond.getString());
	set_cheapest_tile(28);
	execute_cmd("/update", 0);
	STRCMP_EQUAL("App.UpdateHolding("
	"[[2,3,4,5,6,7,8,9,10,11,12,13,27,0],"
	"[15,16,17,18,19,20,21,22,23,24,25,26,28,0]]);", respond.getString());
	tilePool->setCurrentTile(27);
	execute_cmd("/pick", 0);
	STRCMP_EQUAL( "App.Pick(0, 27);App.LightButton('win');", respond.getString());
	execute_cmd("/win", 0);
	STRCMP_EQUAL("App.WinAck(0, 1);", respond.getString());
	execute_cmd("/update", 0);
	STRCMP_EQUAL("App.UpdateHolding([[2,3,4,5,6,7,8,9,10,11,12,13,27,27],[15,16,17,18,19,20,21,22,23,24,25,26,28,0]]);", respond.getString());
	tilePool->setCurrentTile(1);
	set_cheapest_tile(27);
	execute_cmd("/start", 0);
	STRCMP_EQUAL("App.Pick(1, 27);|App.Throw(27, 1);App.UpdateHolding([[14,15,16,17,18,19,20,21,22,23,24,25,26,0],[1,2,3,4,5,6,7,8,9,10,11,12,13,0]]);", respond.getString());
	execute_cmd("/update", 0);
}

TEST(html_game, no_tile_any_more) {
	execute_cmd("/start", 0);
	tilePool->empty();
	execute_cmd("/throw", 1);
	STRCMP_EQUAL(
			"App.Throw(1, 0);|App.WinAck(1, 0);", respond.getString());
	set_cheapest_tile(54);
	execute_cmd("/start", 0);
	STRCMP_EQUAL("App.Pick(1, 54);|App.Throw(54, 1);App.WinAck(0, 0);App.UpdateHolding([[41,42,43,44,45,46,47,48,49,50,51,52,53,0],[28,29,30,31,32,33,34,35,36,37,38,39,40,0]]);", respond.getString());
	execute_cmd("/start", 0);
	STRCMP_EQUAL( "App.Pick(0, 81);App.UpdateHolding([[55,56,57,58,59,60,61,62,63,64,65,66,67,81],[68,69,70,71,72,73,74,75,76,77,78,79,80,0]]);"
	, respond.getString());
}

TEST(html_game, _WIN) {
	execute_cmd("/start", 0);
	execute_cmd("/win", 1);
	STRCMP_EQUAL("alert(\"Are you kidding?\");", respond.getString());
	execute_cmd("/throw", 1);
	STRCMP_EQUAL(
			"App.Throw(1, 0);|App.Pick(1, 28);|App.Throw(14, 1);",
			respond.getString());
	set_cheapest_tile(28);
	execute_cmd("/win", 0);
	STRCMP_EQUAL("alert(\"Are you kidding?\");", respond.getString());
	execute_cmd("/pick", 0);
	set_cheapest_tile(27);
	tilePool->setCurrentTile(27);
	execute_cmd("/throw", 29);
	execute_cmd("/win", 0);
	STRCMP_EQUAL("App.WinAck(0, 1);", respond.getString());
}

TEST(html_game, ai_WIN) {
	execute_cmd("/start", 0);
	tilePool->setCurrentTile(14);
	execute_cmd("/throw", 1);
	STRCMP_EQUAL(
			"App.Throw(1, 0);|App.Pick(1, 14);|App.WinAck(1, 1);",
			respond.getString());
	execute_cmd("/start", 0);
	tilePool->setCurrentTile(41);
	execute_cmd("/pick", 0);
	execute_cmd("/throw", 41);
	STRCMP_EQUAL(
			"App.Throw(41, 0);|App.WinAck(1, 1);",
			respond.getString());
}

TEST(html_game, pong) {
	execute_cmd("/start", 0);
	execute_cmd("/throw", 1);
	execute_cmd("/pong", 0);
	STRCMP_EQUAL( "alert(\"Are you kidding?\");App.UpdateHolding([[2,3,4,5,6,7,8,9,10,11,12,13,27,0],[15,16,17,18,19,20,21,22,23,24,25,26,28,0]]);",
			respond.getString());
	tilePool->setCurrentTile(2);
	execute_cmd("/pick", 0);
	tilePool->setCurrentTile(2);
	set_cheapest_tile(2);
	execute_cmd("/throw", 3);
	STRCMP_EQUAL(
		"App.Throw(3, 0);|App.Pick(1, 2);|App.Throw(2, 1);App.LightButton('pong');",
			respond.getString());
	execute_cmd("/chow", 0);
	STRCMP_EQUAL( "alert(\"Are you kidding?\");App.UpdateHolding("
	"[[2,2,4,5,6,7,8,9,10,11,12,13,27,0],"
	"[15,16,17,18,19,20,21,22,23,24,25,26,28,0]]);",
			respond.getString());
	execute_cmd("/pong", 0);
	STRCMP_EQUAL( "App.UpdateHolding("
"[[4,5,6,7,8,9,10,11,12,13,27,130],"
	"[15,16,17,18,19,20,21,22,23,24,25,26,28,0]]);", respond.getString());
	execute_cmd("/throw", 4);
	STRCMP_EQUAL(
			"App.Throw(4, 0);|App.Pick(1, 3);|App.Throw(15, 1);",
			respond.getString());
}


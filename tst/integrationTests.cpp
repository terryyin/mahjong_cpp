#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "HTMLMahjongGameServer.h"
#include "Wall.h"
#include "EvaluatorAdapter.h"

EvaluatorAdapter * createSimpleEvaluator();
void setCheapestTileForSimpleEvaluator(tile_t tile);

#include "mocks.h"

class EverIncreasingWall: public Wall {
public:
	EverIncreasingWall() :
			Wall(NULL, 0, 0), currentTile_(1), wallEnd_(false) {
	}

	tile_t popATile() {
		return currentTile_++;
	}

	bool isEnd() {
		return wallEnd_;
	}

	void empty() {
		wallEnd_ = true;
	}

	void shuffleAndRebuild() {
	}

	void setCurrentTile(int t) {
		currentTile_ = t;
	}
private:
	tile_t currentTile_;
	bool wallEnd_;
}*lastCreatedEverIncreasingWall = NULL;

static Wall * createEverIncreasingWall() {
	lastCreatedEverIncreasingWall = new EverIncreasingWall;
	return lastCreatedEverIncreasingWall;
}

#define HAS_STRING(expect, actual) HAS_STRING_LOCATION(expect, actual, __FILE__, __LINE__)
TEST_GROUP(html_game) {

	int gameID;
	HTMLMahjongGameServer server;
	HTMLMahjongGameRespond respond;
	EverIncreasingWall *wall;

	void setup() {
		UT_PTR_SET(createEvaluatorAdapter, createSimpleEvaluator);
		UT_PTR_SET(createWall, createEverIncreasingWall);
		server.executeGameCommand("/game", "", &respond);
		gameID = server.getLastGameID();
		wall = lastCreatedEverIncreasingWall;
		execute_cmd("/start", 0);
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
	STRCMP_EQUAL(
			"App.UpdateHolding([[1,2,3,4,5,6,7,8,9,10,11,12,13,27],[14,15,16,17,18,19,20,21,22,23,24,25,26,0]]);App.Pick(0, 27);",
			respond.getString());
}

TEST(html_game, a_game) {
	execute_cmd("/throw", 1);
	HAS_STRING("App.Throw(1, 0);|App.Pick(1, 28);|App.Throw(14, 1);",
			respond.getString());
	setCheapestTileForSimpleEvaluator(28);
	wall->setCurrentTile(27);
	execute_cmd("/pick", 0);
	STRCMP_EQUAL( "App.Pick(0, 27);App.LightButton('win');",
			respond.getString());
	execute_cmd("/win", 0);
	STRCMP_EQUAL("App.WinAck(0, 1);", respond.getString());
	wall->setCurrentTile(1);
	setCheapestTileForSimpleEvaluator(27);
	execute_cmd("/start", 0);
	HAS_STRING(
			"App.UpdateHolding([[14,15,16,17,18,19,20,21,22,23,24,25,26,0],[1,2,3,4,5,6,7,8,9,10,11,12,13,0]]);App.Pick(1, 27);|App.Throw(27, 1);",
			respond.getString());
}

TEST(html_game, no_tile_any_more) {
	wall->empty();
	execute_cmd("/throw", 1);
	STRCMP_EQUAL( "App.Throw(1, 0);|App.WinAck(1, 0);", respond.getString());
	setCheapestTileForSimpleEvaluator(54);
	execute_cmd("/start", 0);
	HAS_STRING(
			"App.UpdateHolding([[41,42,43,44,45,46,47,48,49,50,51,52,53,0],[28,29,30,31,32,33,34,35,36,37,38,39,40,0]]);App.Pick(1, 54);|App.Throw(54, 1);",
			respond.getString());
	HAS_STRING("App.WinAck(0, 0);", respond.getString());
	execute_cmd("/start", 0);
	STRCMP_EQUAL(
			"App.UpdateHolding([[55,56,57,58,59,60,61,62,63,64,65,66,67,81],[68,69,70,71,72,73,74,75,76,77,78,79,80,0]]);App.Pick(0, 81);",
			respond.getString());
}

TEST(html_game, _WIN) {
	execute_cmd("/win", 1);
	STRCMP_EQUAL("alert(\"Are you kidding?\");", respond.getString());
	execute_cmd("/throw", 1);
	HAS_STRING( "App.Throw(1, 0);|App.Pick(1, 28);|App.Throw(14, 1);",
			respond.getString());
	setCheapestTileForSimpleEvaluator(28);
	execute_cmd("/win", 0);
	STRCMP_EQUAL("alert(\"Are you kidding?\");", respond.getString());
	execute_cmd("/pick", 0);
	setCheapestTileForSimpleEvaluator(27);
	wall->setCurrentTile(27);
	execute_cmd("/throw", 29);
	execute_cmd("/win", 0);
	STRCMP_EQUAL("App.WinAck(0, 1);", respond.getString());
}

TEST(html_game, ai_WIN) {
	wall->setCurrentTile(14);
	execute_cmd("/throw", 1);
	STRCMP_EQUAL( "App.Throw(1, 0);|App.Pick(1, 14);|App.WinAck(1, 1);",
			respond.getString());
	execute_cmd("/start", 0);
	wall->setCurrentTile(41);
	execute_cmd("/pick", 0);
	execute_cmd("/throw", 41);
	STRCMP_EQUAL( "App.Throw(41, 0);|App.WinAck(1, 1);", respond.getString());
}

TEST(html_game, pong) {
	execute_cmd("/throw", 1);
	execute_cmd("/pong", 0);
	STRCMP_EQUAL( "alert(\"Are you kidding?\");", respond.getString());
	wall->setCurrentTile(2);
	execute_cmd("/pick", 0);
	wall->setCurrentTile(2);
	setCheapestTileForSimpleEvaluator(2);
	execute_cmd("/throw", 3);
	HAS_STRING(
			"App.Throw(3, 0);|App.Pick(1, 2);|App.Throw(2, 1);App.LightButton('pong');",
			respond.getString());
	execute_cmd("/pong", 0);
	STRCMP_EQUAL( "App.UpdateHolding("
	"[[4,5,6,7,8,9,10,11,12,13,27,130],"
	"[15,16,17,18,19,20,21,22,23,24,25,26,28,0]]);", respond.getString());
	execute_cmd("/throw", 4);
	HAS_STRING( "App.Throw(4, 0);|App.Pick(1, 3);|App.Throw(15, 1);",
			respond.getString());
}

IGNORE_TEST(html_game, chow_when_not_able_to_chow) {
	execute_cmd("/throw", 1);
	execute_cmd("/chow", 0);
	STRCMP_EQUAL( "alert(\"Cannot meld chow.\");", respond.getString());
}

IGNORE_TEST(html_game, chow) {
	setCheapestTileForSimpleEvaluator(14);
	execute_cmd("/throw", 1);
	execute_cmd("/chow", 12);
	STRCMP_EQUAL(
			"App.UpdateHolding([[2,3,4,5,6,7,8,9,10,11,27,268],[15,16,17,18,19,20,21,22,23,24,25,26,28,0]]);",
			respond.getString());
}

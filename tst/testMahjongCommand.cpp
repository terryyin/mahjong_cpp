#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "MahjongCommand.h"
#include "HTMLMahjongGameServer.h"
#include "HTMLMahjongGameRespond.h"
#include "mocks.h"

const int buffer_size = 1000;
const GameID NEW_ID = 100;
const GameID GAME_ID = 101;

TEST_GROUP(MJCommand) {
	char buffer[buffer_size];
	MockHTMLMahjongGameServer server;
	MockHTMLMahjongGameRespond respond;
};

TEST(MJCommand, start_new){
	mock().expectOneCall("startNewGame").onObject(&server).andReturnValue(NEW_ID);
	mock().expectOneCall("newHTMLFrame").onObject(&respond).withParameter("gameID", NEW_ID);
	MJCommandStartNew cmd(&server);
	cmd.execute(&respond);
}

TEST(MJCommand, bye){
	mock().expectOneCall("killGame").onObject(&server).withParameter("gameID", GAME_ID);
	mock().expectOneCall("bye").onObject(&respond);
	MJCommandQuitGame cmd(&server, GAME_ID);
	cmd.execute(&respond);
}

TEST(MJCommand, shutdown){
	mock().expectOneCall("shutdown").onObject(&server);
	mock().expectOneCall("shutdown").onObject(&respond);
	MJCommandShutdownServer cmd(&server);
	cmd.execute(&respond);
}

TEST(MJCommand, start_game){
	MockGame game;
	mock().expectOneCall("update").onObject(&game);
	mock().expectOneCall("set_action").onObject(&game);
	mock().expectOneCall("update").onObject(&respond);
	MJCommandRestart cmd(&server, &game, 123);
	cmd.execute(&respond);
}

TEST(MJCommand, game_does_not_exsit){
	mock().expectOneCall("gameDoesNotExist").onObject(&respond);
	MJCommandDoesNotExist cmd;
	cmd.execute(&respond);
}

TEST(MJCommand, update_game){
	MockGame game;
	mock().expectOneCall("update").onObject(&respond);
	MJCommandUpdate cmd(&server, &game, 123);
	cmd.execute(&respond);
}

TEST(MJCommand, pick){
	MockGame game;
	mock().expectOneCall("update").onObject(&game);
	mock().expectOneCall("set_action").onObject(&game);
	mock().expectOneCall("update").onObject(&respond);
	MJCommandPick cmd(&server, &game, 123);
	cmd.execute(&respond);
}

TEST(MJCommand, discard){
	MockGame game;
	mock().expectOneCall("update").onObject(&game);
	mock().expectOneCall("set_action").onObject(&game);
	mock().expectOneCall("update").onObject(&respond);
	MJCommandDiscard cmd(&server, &game, 123, 1);
	cmd.execute(&respond);
}

TEST(MJCommand, chow){
	MockGame game;
	mock().expectOneCall("update").onObject(&game);
	mock().expectOneCall("set_action").onObject(&game);
	mock().expectOneCall("update").onObject(&respond);
	MJCommandChow cmd(&server, &game, 123, 1);
	cmd.execute(&respond);
}

TEST(MJCommand, pong){
	MockGame game;
	mock().expectOneCall("update").onObject(&game);
	mock().expectOneCall("set_action").onObject(&game);
	mock().expectOneCall("update").onObject(&respond);
	MJCommandPong cmd(&server, &game, 123);
	cmd.execute(&respond);
}

TEST(MJCommand, kong){
	MockGame game;
	mock().expectOneCall("update").onObject(&game);
	mock().expectOneCall("set_action").onObject(&game);
	mock().expectOneCall("update").onObject(&respond);
	MJCommandKong cmd(&server, &game, 123, 1);
	cmd.execute(&respond);
}

TEST(MJCommand, win){
	MockGame game;
	mock().expectOneCall("update").onObject(&game);
	mock().expectOneCall("set_action").onObject(&game);
	mock().expectOneCall("update").onObject(&respond);
	MJCommandWin cmd(&server, &game, 123);
	cmd.execute(&respond);
}


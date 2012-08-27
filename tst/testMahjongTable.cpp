#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TilePool.h"
#include "mj_table.h"
#include "mocks.h"

TEST_GROUP(MahjongTable) {

};

TEST(MahjongTable, should_not_restart_when_one_player_send_restart_request) {
	TilePool pool;
	MockPerspective perspective1;
	MockPerspective perspective2;

	MahjongTable table(&pool);
	table.addPlayer(&perspective1);
	table.addPlayer(&perspective2);

	mock().expectOneCall("agent.get_action.tile").onObject(&perspective1).andReturnValue(1);
	mock().expectOneCall("agent.get_action").onObject(&perspective1).andReturnValue(ACTION_RESTART);
	mock().expectOneCall("agent.get_action").onObject(&perspective2).andReturnValue(NO_ACTION);
	CHECK(!table.doPlayerAction());
}

TEST(MahjongTable, should_restart_when_all_players_send_restart_request) {
	TilePool pool;
	MockPerspective perspective1;
	MockPerspective perspective2;

	MahjongTable table(&pool);
	table.addPlayer(&perspective1);
	table.addPlayer(&perspective2);

	mock().expectOneCall("agent.get_action.tile").onObject(&perspective1).andReturnValue(1);
	mock().expectOneCall("agent.get_action").onObject(&perspective1).andReturnValue(ACTION_RESTART);
	mock().expectOneCall("agent.get_action").onObject(&perspective2).andReturnValue(ACTION_RESTART);
	mock().expectOneCall("agent.deal").onObject(&perspective1).ignoreOtherParameters();
	mock().expectOneCall("agent.deal").onObject(&perspective2).ignoreOtherParameters();
	mock().expectOneCall("agent.deal").onObject(&perspective1).ignoreOtherParameters();
	mock().expectOneCall("agent.deal").onObject(&perspective2).ignoreOtherParameters();
	mock().ignoreOtherCalls();
	CHECK(table.doPlayerAction());
}

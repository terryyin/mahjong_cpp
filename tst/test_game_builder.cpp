#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "game_builder.h"
#include "ui_agent.h"


TEST_GROUP(system1) {

};

/*
 * This is a bad example
 * of a test case, which covers many line of code,
 * but actually checks nothing.
 */
TEST(system1, create_system) {
	UIAgent * ui = Game::join_new_game_with_one_ai_player(NULL);
	delete ui;
}


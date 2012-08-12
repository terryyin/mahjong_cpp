#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "tiles.h"
#include "ai_agent.h"

#include "mocks.h"

TEST_GROUP(ai_agent)
{
	Agent * agent;
	void setup() {
		agent = create_ai_agent();
		tile_t holdings[] = { C(1) };
		agent->deal(holdings, 1, 0);
	}
	void teardown() {
		delete agent;
	}

};

TEST(ai_agent, player_creation)
{
	LONGS_EQUAL(ACTION_RESTART, agent->get_action(NULL));
}

TEST(ai_agent, player_pick_when_winning)
{
	agent->pick(C(1), 0);
	LONGS_EQUAL(ACTION_WIN, agent->get_action(NULL));
}

TEST(ai_agent, player_react_when_winning)
{
	agent->discard_tile(C(1), 1);
	LONGS_EQUAL(ACTION_WIN, agent->get_action(NULL));
}

TEST(ai_agent, player_pick)
{
	mock()	.expectNCalls(2, "evaluator_evaluate_array")
			.ignoreOtherParameters()
			.andReturnValue(1);
	agent->pick(C(3), 0);
	LONGS_EQUAL(ACTION_DISCARD, agent->get_action(NULL));
}

TEST(ai_agent, player_win)
{
	agent->win(0, 0);
	LONGS_EQUAL(ACTION_RESTART, agent->get_action(NULL));
}

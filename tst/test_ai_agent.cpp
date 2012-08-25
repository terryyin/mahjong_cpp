#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "tiles.h"
#include "AIPerspective.h"

#include "mocks.h"

TEST_GROUP(ai_agent)
{
	AIPerspective * agent;
	Evaluator * evaluator;
	void setup() {
		evaluator = createMockEvaluator();
		agent = new AIPerspective();
		agent->setEvaluator(evaluator);
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
	// ai player will call the evaluator to evaluate the array
	// twice, because there are two tiles after pick.
	mock()	.expectNCalls(2, "evaluate_array")
			.onObject(evaluator)
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

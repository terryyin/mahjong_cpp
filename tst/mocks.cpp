#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "tile_pool.h"
#include "player.h"
#include "agent.h"

#include "stdio.h"
#include "mocks.h"

#include "../mahjong_evaluator/include/mj_evaluator.h"
#include "evaluator.h"
/*
 * This a bad example of mocking 3rd-party code.
 * LIB_xxx are 3rd-party functions.
 * In our test, we write a stub for it, and make it as a mock.
 * The better solution is to write an adaptor for LIB_xxx functions
 * and then mock the adaptor.
 */
int LIB_evaluator_evaluate_array(Evaluator* self, tile_t tiles[],
		int array_size) {
	return mock().actualCall("LIB_evaluator_evaluate_array").withParameter("tiles",
			tiles).withParameter("array_size", array_size).returnValue().getIntValue();
}
Evaluator* LIB_create_evaluator(void) {
	return NULL;
}
void LIB_evaluator_destroy(Evaluator*) {
}

class MockEvaluator: public Evaluator{
public:
	MockEvaluator() {}
	virtual ~MockEvaluator(){}
	virtual int evaluate_array(tile_t tiles[], int array_size){
		return mock().actualCall("evaluate_array").onObject(this).withParameter("tiles",
				tiles).withParameter("array_size", array_size).returnValue().getIntValue();
	}
};
Evaluator * createMockEvaluator(void)
{
	return new MockEvaluator();
}


static void tile_pool_shuffle_mock(tile_pool_t * game) {
	mock().actualCall("tile_pool_shuffle");
}

static int tile_pool_is_end_mock(tile_pool_t * game) {
	return mock().actualCall("tile_pool_is_end").onObject((game)).returnValue().getIntValue();
}

static tile_t tile_pool_pop_a_tile_mock(tile_pool_t * self) {
	return (tile_t) mock().actualCall("tile_pool_pop_a_tile").onObject(self).returnValue().getIntValue();
}

/*
 * tile_pool is an ADT (Abstract DataType).
 * It doesn't support polymorphism (function pointers stored in data structure).
 * All the methods of tile_pool are global function pointers.
 * To mock an ADT object, we simply redirect the methods to our mock functions.
 */
void setup_tile_pool_mocks() {
	UT_PTR_SET(tile_pool_shuffle, tile_pool_shuffle_mock);
	UT_PTR_SET(tile_pool_is_end, tile_pool_is_end_mock);
	UT_PTR_SET(tile_pool_pop_a_tile, tile_pool_pop_a_tile_mock);
}

#include "agent.h"
/*
 *  Using CppUMock to implement mock for agent.
 */
class AgentMock: public Agent {
public:
	virtual void destroy(Agent *self) {
		free(self);
	}
	virtual void deal(tile_t tiles[], int buffer_size, int distance) {
		char s[100];
		mock().actualCall("agent.deal").onObject(this).withParameter("distance",
				distance).withParameter("tiles",
				tiles_to_string(tiles, buffer_size, s, 100));
	}
	virtual action_t get_action(tile_t* tile) {
		if (tile != NULL)
			*tile =
					mock().actualCall("agent.get_action.tile").onObject(this).returnValue().getIntValue();
		return (action_t) mock().actualCall("agent.get_action").onObject(this).returnValue().getIntValue();
	}
	virtual void pick(tile_t tile, int distance) {
		mock().actualCall("agent.pick").onObject(this).withParameter("tile",
				tile).withParameter("distance", distance);
	}
	virtual void win(int score, int distance) {
		mock().actualCall("agent.win").onObject(this).withParameter("score",
				score).withParameter("distance", distance);
	}
	virtual void discard_tile(tile_t tile, int distance) {
		mock().actualCall("agent.discard_tile").onObject(this).withParameter(
				"tile", tile).withParameter("distance", distance);
	}
	virtual void pong(tile_t tile, int distance){}
	virtual int chow(tile_t tile, tile_t with, int distance){return 0;}
	virtual void set_action(action_t action, tile_t tile){}

};
Agent * create_mock_agent(void) {
	Agent * agent = new AgentMock();
	return agent;
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "TilePool.h"
#include "PlayerTiles.h"
#include "Perspective.h"

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

class MockTilePool:public TilePool{
public:
	MockTilePool(){}
	~MockTilePool(){}
	void shuffle() {
		mock().actualCall("tile_pool_shuffle").onObject(this);
	}

	int is_end() {
		return mock().actualCall("tile_pool_is_end").onObject(this).returnValue().getIntValue();
	}

	tile_t pop_a_tile() {
		return (tile_t) mock().actualCall("tile_pool_pop_a_tile").onObject(this).returnValue().getIntValue();
	}
};


TilePool * create_tile_pool_mocks() {
	return new MockTilePool();
}


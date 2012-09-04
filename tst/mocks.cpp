#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "Wall.h"
#include "Hand.h"
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
int LIB_evaluator_evaluate_array(mahjong_evaluator_handle_t* self, tile_t tiles[],
		int array_size) {
	return mock().actualCall("LIB_evaluator_evaluate_array").withParameter("tiles",
			tiles).withParameter("array_size", array_size).returnValue().getIntValue();
}
mahjong_evaluator_handle_t* LIB_create_evaluator(void) {
	return NULL;
}
void LIB_evaluator_destroy(mahjong_evaluator_handle_t*) {
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

class MockWall:public Wall{
public:
	MockWall():Wall(NULL, 0, 0){}
	~MockWall(){}
	void shuffleAndRebuild() {
		mock().actualCall("shuffleAndRebuild").onObject(this);
	}

	bool isEnd() {
		return mock().actualCall("isEnd").onObject(this).returnValue().getIntValue();
	}

	tile_t popATile() {
		return (tile_t) mock().actualCall("popATile").onObject(this).returnValue().getIntValue();
	}
};

Wall * createMockWall() {
	return new MockWall();
}

class Dependency {

};

class Singleton {
private:
	Singleton() {
	}

public:
	Singleton * getInstance() {
		if (instance_ == NULL)
			instance_ = new Singleton;
		return instance_;
	}
	void setInstance(Singleton * new_instance) {
		delete instance_;
		instance_ = new_instance;
	}
private:
	static Singleton * instance_;
};

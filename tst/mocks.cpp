#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "Wall.h"
#include "Hand.h"
#include "Perspective.h"
#include "EvaluatorAdapter.h"
#include "mocks.h"

class MockEvaluator: public EvaluatorAdapter{
public:
	MockEvaluator() {}
	virtual ~MockEvaluator(){}
	virtual int evaluate_array(tile_t tiles[], int array_size){
		return mock().actualCall("evaluate_array").onObject(this).withParameter("tiles",
				tiles).withParameter("array_size", array_size).returnValue().getIntValue();
	}
};
EvaluatorAdapter * createMockEvaluator(void)
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

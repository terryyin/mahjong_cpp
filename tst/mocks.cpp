#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "Wall.h"
#include "Hand.h"
#include "Perspective.h"
#include "EvaluatorAdaptor.h"
#include "mocks.h"

class MockEvaluator: public EvaluatorAdaptor{
public:
	MockEvaluator() {}
	virtual ~MockEvaluator(){}
	virtual int evaluate_array(const TileArray& tiles){
		return mock().actualCall("evaluate_array").onObject(this).withParameter("tiles",
				(void*)&tiles).returnValue().getIntValue();
	}
};
EvaluatorAdaptor * createMockEvaluator(void)
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

	Tile popATile() {
		return (Tile) mock().actualCall("popATile").onObject(this).returnValue().getIntValue();
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

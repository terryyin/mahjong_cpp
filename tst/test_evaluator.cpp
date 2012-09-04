#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "tiles.h"
#include "evaluator.h"

TEST_GROUP(Evaluator) {

};

TEST(Evaluator, evaluator_array){
	const int SCORE = 100;
	mock().expectOneCall("LIB_evaluator_evaluate_array")
			.withParameter("tiles", "")
			.withParameter("array_size", 0)
			.andReturnValue(SCORE);
	Evaluator * evaluator = createEvaluator();
	LONGS_EQUAL(SCORE, evaluator->evaluate_array(NULL, 0));
	delete evaluator;
}

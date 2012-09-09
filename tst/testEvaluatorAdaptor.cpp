#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "tiles.h"
#include "EvaluatorAdaptor.h"
#include "../mahjong_evaluator/include/mj_evaluator.h"

TEST_GROUP(EvaluatorAdaptor) {

};

TEST(EvaluatorAdaptor, notNamedYet) {
	EvaluatorAdaptor * evaluator = createEvaluatorAdaptor();

	//exercise: start from here

	delete evaluator;
}

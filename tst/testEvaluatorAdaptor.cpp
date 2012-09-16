#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "TileArray.h"
#include "EvaluatorAdaptor.h"
#include "mj_evaluator.h"

TEST_GROUP(EvaluatorAdaptor) {

};

TEST(EvaluatorAdaptor, notNamedYet) {
	EvaluatorAdaptor * evaluator = createEvaluatorAdaptor();

	//exercise: start from here

	delete evaluator;
}

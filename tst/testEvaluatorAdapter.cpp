#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "tiles.h"
#include "EvaluatorAdapter.h"

TEST_GROUP(EvaluatorAdapter) {

};

TEST(EvaluatorAdapter, notNamedYet) {
	EvaluatorAdapter * evaluator = createEvaluatorAdapter();

	// Exercise: start from here.

	delete evaluator;
}

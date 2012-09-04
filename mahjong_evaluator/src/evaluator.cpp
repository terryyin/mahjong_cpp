
extern "C" {
#include "mj_evaluator.h"
#include "terry_evaluator.h"
}

struct mahjong_evaluator_handle_t {
};


mahjong_evaluator_handle_t * LIB_create_evaluator(void)
{
	return new mahjong_evaluator_handle_t;
}
void LIB_evaluator_destroy(mahjong_evaluator_handle_t * e)
{
	delete e;
}

int LIB_evaluator_evaluate_array(mahjong_evaluator_handle_t * self, tile_t tiles[], int array_size)
{
	return terry_ai_evaluate_array(tiles, array_size);
}

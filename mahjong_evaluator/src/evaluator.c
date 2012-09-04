#include "mj_evaluator.h"
#include "terry_evaluator.h"

mahjong_evaluator_handle_t LIB_create_evaluator(void)
{
	return 1;
}
void LIB_evaluator_destroy(mahjong_evaluator_handle_t e)
{
}

int LIB_evaluator_evaluate_array(mahjong_evaluator_handle_t handle, tile_t tiles[], int array_size)
{
	return terry_ai_evaluate_array(tiles, array_size);
}

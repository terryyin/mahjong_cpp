#ifndef MJ_mahjong_evaluator_handle_t_H_
#define MJ_mahjong_evaluator_handle_t_H_

#include "tile.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct mahjong_evaluator_handle_t;

mahjong_evaluator_handle_t* LIB_create_evaluator(void);
void LIB_evaluator_destroy(mahjong_evaluator_handle_t*);
int LIB_evaluator_evaluate_array(mahjong_evaluator_handle_t* self, tile_t tiles[], int array_size);

#ifdef __cplusplus
}
#endif
#endif /* MJ_mahjong_evaluator_handle_t_H_ */

#include "game_builder.h"
#include "tile_pool.h"
#include "mj_table.h"
#include "player.h"
#include "ui_agent.h"
#include "ai_agent.h"

UIAgent * game_builder_join_new_game_with_one_ai_player(struct user_info_t * user)
{
	tile_pool_t * pool = create_tile_pool();
	mj_table_t * table = create_mj_table(pool);
	Agent * ai_agent = create_ai_agent();
	UIAgent * agent = create_ui_agent();
	agent->set_game_flow(table);
	mj_table_add_player(table, agent);
	mj_table_add_player(table, ai_agent);

	return agent;
}

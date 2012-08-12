#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "mocks.h"
#include "ui_agent.h"

TEST_GROUP(ui_agent)
{
	UIAgent * agent;
	ui_event_t event;
	tile_t tile;
	char buffer[1000];
	void setup() {
		agent = create_ui_agent();
	}
	void teardown() {
		delete agent;
	}
};

TEST(ui_agent, pop_nothing_when_empty)
{
	LONGS_EQUAL(0, agent->pop_event(&event));
}
TEST(ui_agent, before_distribution)
{
	STRCMP_EQUAL("[]", agent->get_tiles_array_string(buffer, 1000));
}

TEST(ui_agent, event_deal)
{
	tile_t tiles[] = { MJ_NORTH };

	agent->deal(tiles, 1, 0);
	LONGS_EQUAL(0, agent->pop_event(&event));
	STRCMP_EQUAL("[[117,0]]", agent->get_tiles_array_string(buffer, 1000));
}

TEST(ui_agent, event_pick)
{
	tile_t tiles[] = { MJ_EAST };

	agent->deal(tiles, 1, 0);
	agent->pick(MJ_NORTH, 0);

	LONGS_EQUAL(1, agent->pop_event(&event));
	LONGS_EQUAL(UI_EVENT_PICK, event.event);
	LONGS_EQUAL(MJ_NORTH, event.tiles[0]);
	LONGS_EQUAL(0, agent->pop_event(&event));
}

TEST(ui_agent, event_pick_and_win)
{
	tile_t tiles[] = { MJ_EAST };

	agent->deal(tiles, 1, 0);
	agent->pick(MJ_EAST, 0);

	LONGS_EQUAL(1, agent->pop_event(&event));
	LONGS_EQUAL(UI_EVENT_PICK, event.event);
	LONGS_EQUAL(1, agent->pop_event(&event));
	LONGS_EQUAL(UI_EVENT_WIN_ABLE, event.event);
	LONGS_EQUAL(0, agent->pop_event(&event));
}

TEST(ui_agent, action_get_empty)
{
	LONGS_EQUAL(NO_ACTION, agent->get_action(&tile));
}

TEST(ui_agent, action_set_and_get)
{
	agent->set_action(ACTION_DISCARD, MJ_EAST);

	LONGS_EQUAL(ACTION_DISCARD, agent->get_action(&tile));
	LONGS_EQUAL(MJ_EAST, tile);
}

TEST(ui_agent, event_discard)
{
	tile_t tiles[] = { MJ_NORTH };

	agent->deal(tiles, 1, 0);
	agent->discard_tile(MJ_NORTH, 0);

	LONGS_EQUAL(1, agent->pop_event(&event));
	LONGS_EQUAL(UI_EVENT_DISCARD, event.event);
	LONGS_EQUAL(MJ_NORTH, event.tiles[0]);
	LONGS_EQUAL(0, agent->pop_event(&event));
}

IGNORE_TEST(ui_agent, other_player_discard)
{
	tile_t tiles[] = { C(1),C(2),C(3),C(3) };

	agent->deal(tiles, 4, 0);
	agent->discard_tile(MJ_NORTH, 1);

	LONGS_EQUAL(1, agent->pop_event(&event));
	LONGS_EQUAL(UI_EVENT_DISCARD, event.event);
	LONGS_EQUAL(MJ_NORTH, event.tiles[0]);
	LONGS_EQUAL(0, agent->pop_event(&event));
}

TEST(ui_agent, other_player_discard_and_play_can_do_some_reaction)
{
	tile_t tiles[] = { C(1),C(1),C(3),C(3) };

	agent->deal(tiles, 4, 0);
	agent->discard_tile(C(1), 1);

	LONGS_EQUAL(1, agent->pop_event(&event));
	LONGS_EQUAL(UI_EVENT_DISCARD, event.event);
	LONGS_EQUAL(1, agent->pop_event(&event));
	LONGS_EQUAL(UI_EVENT_WIN_ABLE, event.event);
	LONGS_EQUAL(1, agent->pop_event(&event));
	LONGS_EQUAL(UI_EVENT_PONG_ABLE, event.event);
}

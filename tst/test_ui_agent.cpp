#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "mocks.h"
#include "UserPerspective.h"
#include <typeinfo>

TEST_GROUP(UserPerspective)
{
	UserPerspective * agent;
	UIEvent *event;
	tile_t tile;
	char buffer[1000];
	void setup() {
		agent = createUserPerspective();
	}
	void teardown() {
		delete agent;
	}
};

TEST(UserPerspective, pop_nothing_when_empty)
{
	CHECK_EQUAL(NULL, agent->popEvent());
}
TEST(UserPerspective, before_distribution)
{
	STRCMP_EQUAL("[]", agent->get_tiles_array_string(buffer, 1000));
}

TEST(UserPerspective, event_deal)
{
	tile_t tiles[] = { MJ_NORTH };

	agent->deal(tiles, 1, 0);
	CHECK_EQUAL(NULL, agent->popEvent());
	STRCMP_EQUAL("[[117,0]]", agent->get_tiles_array_string(buffer, 1000));
}

TEST(UserPerspective, event_pick)
{
	tile_t tiles[] = { MJ_EAST };

	agent->deal(tiles, 1, 0);
	agent->pick(MJ_NORTH, 0);

	event = agent->popEvent();
	STRCMP_EQUAL(typeid(HTMLPickEvent).name(), typeid(*event).name());
	delete event;
	CHECK_EQUAL(NULL, agent->popEvent());
}

TEST(UserPerspective, event_pick_and_win)
{
	tile_t tiles[] = { MJ_EAST };

	agent->deal(tiles, 1, 0);
	agent->pick(MJ_EAST, 0);

	event = agent->popEvent();
	STRCMP_EQUAL(typeid(HTMLPickEvent).name(), typeid(*event).name());
	delete event;
	event = agent->popEvent();
	STRCMP_EQUAL(typeid(HTMLEnableWinEvent).name(), typeid(*event).name());
	delete event;
	CHECK_EQUAL(NULL, agent->popEvent());
}

TEST(UserPerspective, action_get_empty)
{
	LONGS_EQUAL(NO_ACTION, agent->get_action(&tile));
}

TEST(UserPerspective, action_set_and_get)
{
	agent->set_action(ACTION_DISCARD, MJ_EAST);

	LONGS_EQUAL(ACTION_DISCARD, agent->get_action(&tile));
	LONGS_EQUAL(MJ_EAST, tile);
}

TEST(UserPerspective, event_discard)
{
	tile_t tiles[] = { MJ_NORTH };

	agent->deal(tiles, 1, 0);
	agent->discard_tile(MJ_NORTH, 0);

	event = agent->popEvent();
	STRCMP_EQUAL(typeid(HTMLDiscardEvent).name(), typeid(*event).name());
	delete event;
	CHECK_EQUAL(NULL, agent->popEvent());
}

TEST(UserPerspective, other_player_discard_and_play_can_do_some_reaction)
{
	tile_t tiles[] = { C(1),C(1),C(3),C(3) };

	agent->deal(tiles, 4, 0);
	agent->discard_tile(C(1), 1);

	event = agent->popEvent();
	STRCMP_EQUAL(typeid(HTMLDiscardEvent).name(), typeid(*event).name());
	delete event;
	event = agent->popEvent();
	STRCMP_EQUAL(typeid(HTMLEnableWinEvent).name(), typeid(*event).name());
	delete event;
	event = agent->popEvent();
	STRCMP_EQUAL(typeid(HTMLEnablePongEvent).name(), typeid(*event).name());
	delete event;
}

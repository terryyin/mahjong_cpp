#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "mocks.h"
#include "UserPerspective.h"
#include "HTMLUIEvent.h"
#include "mocks.h"

class DummyUIEvent: public UIEvent {
public:
	virtual ~DummyUIEvent() {
	}
	virtual std::string toString() {
		return "";
	}
};

const tile_t WINNING_TILE = 1;

TEST_GROUP(UserPerspective) {
	UserPerspective * userPerspective;
	UIEvent *event;
	DummyUIEvent dummyEvent;
	DummyUIEvent dummyEvent1;
	DummyUIEvent dummyEvent2;
	tile_t tile;
	char buffer[1000];
	void setup() {
		MockUIEventFactory *eventFactory = new MockUIEventFactory;
		userPerspective = new UserPerspective(eventFactory);
	}
	void teardown() {
		delete userPerspective;
	}
	void deal() {
		tile_t tiles[] = { WINNING_TILE, WINNING_TILE, WINNING_TILE+2, WINNING_TILE+2 };

		mock().expectOneCall("createDealEvent").withParameter("view",
				(UserView *) userPerspective).andReturnValue(&dummyEvent);
		userPerspective->deal(tiles, 4, 0);
		CHECK_EQUAL(&dummyEvent, userPerspective->popEvent());
	}
};

TEST(UserPerspective, pop_nothing_when_empty) {
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}
TEST(UserPerspective, before_distribution) {
	CHECK_EQUAL(0, userPerspective->getNumberOfPlayer());
}

TEST(UserPerspective, event_deal) {
	deal();
}

TEST(UserPerspective, event_pick) {
	deal();

	mock().expectOneCall("createPickEvent").withParameter("tile",
			WINNING_TILE+1).withParameter("distance", 0).andReturnValue(&dummyEvent1);

	userPerspective->pick(WINNING_TILE+1, 0);

	CHECK_EQUAL(&dummyEvent1, userPerspective->popEvent());
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, event_pick_and_win) {
	deal();

	mock().expectOneCall("createPickEvent").withParameter("tile",
			WINNING_TILE).withParameter("distance", 0).andReturnValue(&dummyEvent1);
	mock().expectOneCall("createEnableWinEvent").andReturnValue(&dummyEvent2);

	userPerspective->pick(WINNING_TILE, 0);

	CHECK_EQUAL(&dummyEvent1, userPerspective->popEvent());
	CHECK_EQUAL(&dummyEvent2, userPerspective->popEvent());
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, action_get_empty) {
	LONGS_EQUAL(NO_ACTION, userPerspective->popActionRequest(&tile));
}

TEST(UserPerspective, action_set_and_get) {
	userPerspective->set_action(ACTION_DISCARD, MJ_EAST);

	LONGS_EQUAL(ACTION_DISCARD, userPerspective->popActionRequest(&tile));
	LONGS_EQUAL(MJ_EAST, tile);
}

TEST(UserPerspective, event_discard) {
	deal();

	mock().expectOneCall("createDiscardEvent").withParameter("tile",
			WINNING_TILE).withParameter("distance", 0).andReturnValue(&dummyEvent1);

	userPerspective->discard_tile(WINNING_TILE, 0);

	CHECK_EQUAL(&dummyEvent1, userPerspective->popEvent());
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, event_pong) {
	deal();

	mock().expectOneCall("createEnableWinEvent").andReturnValue(&dummyEvent1);
	mock().expectOneCall("createDealEvent").ignoreOtherParameters().andReturnValue(&dummyEvent2);

	userPerspective->pong(WINNING_TILE, 0);

	POINTERS_EQUAL(&dummyEvent2, userPerspective->popEvent());
	POINTERS_EQUAL(&dummyEvent1, userPerspective->popEvent());
	POINTERS_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, event_chow) {
	deal();

	mock().expectOneCall("createDealEvent").ignoreOtherParameters().andReturnValue(&dummyEvent1);

	userPerspective->chow(WINNING_TILE+1, WINNING_TILE, 0);

	POINTERS_EQUAL(&dummyEvent1, userPerspective->popEvent());
	POINTERS_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, other_player_discard_and_play_can_do_some_reaction) {
	deal();

	mock().expectOneCall("createDiscardEvent").withParameter("tile",
			WINNING_TILE).withParameter("distance", 1).andReturnValue(&dummyEvent1);
	mock().expectOneCall("createEnableWinEvent").andReturnValue(&dummyEvent2);
	mock().expectOneCall("createEnablePongEvent").andReturnValue(&dummyEvent2);

	userPerspective->discard_tile(WINNING_TILE, 1);

	CHECK_EQUAL(&dummyEvent1, userPerspective->popEvent());
	CHECK_EQUAL(&dummyEvent2, userPerspective->popEvent());
	CHECK_EQUAL(&dummyEvent2, userPerspective->popEvent());
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}

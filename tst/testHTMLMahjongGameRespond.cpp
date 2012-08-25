#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "HTMLMahjongGameRespond.h"
#include "mocks.h"
#include "HTMLUIEvent.h"
#include "PlayerTiles.h"

TEST_GROUP(HTMLMahjongGameRespond) {
	HTMLMahjongGameRespond respond;
	MockUserView view;
};

TEST(HTMLMahjongGameRespond, new_game){
	respond.newGame(123);
	const char * resp = respond.getString();
	CHECK(strstr(resp, "<script>game_id=123;</script>"));
}

TEST(HTMLMahjongGameRespond, bye){
	respond.bye();
	STRCMP_EQUAL("", respond.getString());
}

TEST(HTMLMahjongGameRespond, shutdown){
	respond.shutdown();
	const char * resp = respond.getString();
	CHECK(strstr(resp, "shutdown"));
}

TEST(HTMLMahjongGameRespond, game_does_not_exist){
	respond.gameDoesNotExist();
	const char * resp = respond.getString();
	STRCMP_EQUAL("alert('Game does not exist. Restart, please.');", resp);
}

TEST(HTMLMahjongGameRespond, updateUIEvent_when_no_event){
	mock().expectOneCall("popEvent").onObject(&view).andReturnValue((void*)NULL);
	respond.updateUIEvent(&view);
	STRCMP_EQUAL("", respond.getString());
}

class MockUIEvent: public UIEvent {
public:
	std::string toString() {
		return mock().actualCall("toString").onObject(this).returnValue().getStringValue();
	}
};

TEST(HTMLMahjongGameRespond, updateUIEvent_when_one_event){
	UIEvent * event = new MockUIEvent;
	mock().expectOneCall("popEvent").onObject(&view).andReturnValue(event);
	mock().expectOneCall("toString").onObject(event).andReturnValue("EVENT");
	mock().expectOneCall("popEvent").onObject(&view).andReturnValue((void*)NULL);
	respond.updateUIEvent(&view);
	STRCMP_EQUAL("EVENT", respond.getString());
}

TEST(HTMLMahjongGameRespond, before_distribution)
{
	mock().expectOneCall("getNumberOfPlayer").onObject(&view).andReturnValue(0);
	respond.updateAllHoldings(&view);
	STRCMP_EQUAL("App.UpdateHolding([]);", respond.getString());
}

TEST(HTMLMahjongGameRespond, event_deal)
{
	tile_t tiles1[] = { 1 };
	tile_t tiles2[] = { 2, 3 };
	PlayerTiles playerData1, playerData2;
	playerData1.deal(tiles1, 1);
	playerData2.deal(tiles2, 2);

	mock().expectOneCall("getNumberOfPlayer").onObject(&view).andReturnValue(2);
	mock().expectOneCall("getPlayerData").onObject(&view).andReturnValue(&playerData1);
	mock().expectOneCall("getPlayerData").onObject(&view).andReturnValue(&playerData2);;
	respond.updateAllHoldings(&view);
	STRCMP_EQUAL("App.UpdateHolding([[1,0],[2,3,0]]);", respond.getString());
}


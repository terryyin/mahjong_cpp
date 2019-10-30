#include "CppUTestExt/GMock.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "HTMLMahjongGameRespond.h"
#include "mocks.h"
#include "HTMLUIEvent.h"
#include "Hand.h"
#include "string.h"

using ::testing::_;

class GMockUserView: public UserView {
public:
	MOCK_METHOD0(popEvent, UIEvent * ());
	MOCK_METHOD2(get_tiles_array_string, const char * (char buffer[], int buffer_size));
	MOCK_METHOD0(getNumberOfPlayer, int ());
	MOCK_METHOD1(getHand, Hand *(int));
};

TEST_GROUP(HTMLMahjongGameRespond) {
	HTMLMahjongGameRespond respond;
	GMockUserView view;
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
	EXPECT_CALL(view, popEvent()).Times(1).WillOnce(Return((UIEvent *)NULL));
	respond.updateUIEvent(&view);
	STRCMP_EQUAL("", respond.getString());
}

class MockUIEvent: public UIEvent {
public:
	MOCK_METHOD0(toString, std::string () );
};

TEST(HTMLMahjongGameRespond, updateUIEvent_when_one_event){
	MockUIEvent * event = new MockUIEvent;
	EXPECT_CALL(view, popEvent()).Times(2).WillOnce(Return((UIEvent *)event)).WillOnce(Return((UIEvent *)NULL));
	EXPECT_CALL(*event, toString()).Times(1).WillOnce(Return("EVENT"));
	respond.updateUIEvent(&view);
	STRCMP_EQUAL("EVENT", respond.getString());
}

TEST(HTMLMahjongGameRespond, before_distribution)
{
	EXPECT_CALL(view, getNumberOfPlayer()).Times(1).WillOnce(Return(0));
	respond.updateAllHoldings(&view);
	STRCMP_EQUAL("App.UpdateHolding([]);", respond.getString());
}

TEST(HTMLMahjongGameRespond, event_deal)
{
	Tile tiles1[] = { 1 };
	Tile tiles2[] = { 2, 3 };
	Hand playerData1, playerData2;
	playerData1.deal(tiles1, 1);
	playerData2.deal(tiles2, 2);

	EXPECT_CALL(view, getNumberOfPlayer()).Times(1).WillOnce(Return(2));
	EXPECT_CALL(view, getHand(_)).Times(2).WillOnce(Return(&playerData1)).WillOnce(Return(&playerData2));
	respond.updateAllHoldings(&view);
	STRCMP_EQUAL("App.UpdateHolding([[1,0],[2,3,0]]);", respond.getString());
}


#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "HTMLMahjongGameRespond.h"
#include "mocks.h"
#include "HTMLUIEvent.h"

TEST_GROUP(HTMLMahjongGameRespond) {
	HTMLMahjongGameRespond respond;
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
	MockUserView view;
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
	MockUserView view;
	UIEvent * event = new MockUIEvent;
	mock().expectOneCall("popEvent").onObject(&view).andReturnValue(event);
	mock().expectOneCall("toString").onObject(event).andReturnValue("EVENT");
	mock().expectOneCall("popEvent").onObject(&view).andReturnValue((void*)NULL);
	respond.updateUIEvent(&view);
	STRCMP_EQUAL("EVENT", respond.getString());
}

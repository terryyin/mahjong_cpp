#include "CppUTestExt/GMock.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "HTMLCommandParser.h"
#include "MahjongCommand.h"
#include <typeinfo>
#include "mocks.h"

class GMockHTMLMahjongGameServer: public MahjongGameServer {
public:
	MOCK_METHOD0(startNewGamem, GameID ());
	MOCK_METHOD1(killGame, void (GameID));
	MOCK_METHOD0(shutdown, void ());
	MOCK_METHOD1(getGameByID, Game * (GameID));
};

TEST_GROUP(HTMLCommandParserWithGMock) {
	GMockHTMLMahjongGameServer server;
	HTMLCommandParser *parser;
	MahjongCommand *cmd;
	void setup() {
		cmd = NULL;
		parser = new HTMLCommandParser(&server);
	}
	void teardown() {
		delete cmd;
		delete parser;
	}
};

using ::testing::_;
TEST(HTMLCommandParserWithGMock, restart) {
	UserPerspective game;
	EXPECT_CALL(server, getGameByID(_)).Times(1).WillOnce(Return((Game *)&game));
	cmd = parser->parse("/start", "3000");
	STRCMP_EQUAL(typeid(MJCommandRestart).name(), typeid(*cmd).name());
}


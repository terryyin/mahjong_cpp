#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "HTMLMahjongGameServer.h"
#include "HTMLCommandParser.h"
#include "MahjongCommand.h"
#include "mocks.h"

static void shutdown_callback() {
	mock().actualCall("shutdown_callback");
}

class MockHTMLCommandParser: public HTMLCommandParser {
public:
	MockHTMLCommandParser() :
			HTMLCommandParser(NULL) {

	}
	MahjongCommandBase * parse(const char * command, const char *parameters) {
		return (MahjongCommandBase *) mock().actualCall("parse").onObject(this).withParameter(
				"command", command).withParameter("parameters", parameters).returnValue().getObjectPointer();
	}
};

class MockMahjongCommand: MahjongCommandBase {
public:
	virtual void execute(MahjongGameRespond *respond) {
		if (mock().hasData("string passing to respond"))
			respond->setString(
					mock().getData("string passing to respond").getStringValue());
		mock().actualCall("execute").onObject(this);
	}
};

TEST_GROUP(HTMLMahjongGameServer) {
	HTMLMahjongGameServer *server;
	MockHTMLCommandParser *parser;
	void setup() {
		parser = new MockHTMLCommandParser;
		server = new HTMLMahjongGameServer(shutdown_callback, parser);
	}
	void teardown() {
		delete server;
	}
};

TEST(HTMLMahjongGameServer, callback_should_be_call_when_shutdown) {
	mock().expectOneCall("shutdown_callback");
	server->shutdown();
}

TEST(HTMLMahjongGameServer, execute_command) {
	const int buffer_size = 1000;
	char buffer[buffer_size];
	MockMahjongCommand *command = new MockMahjongCommand;

	mock().expectOneCall("parse").onObject(parser).withParameter("command",
			"command").withParameter("parameters", "parameters").andReturnValue(
			(void*) command);
	mock().expectOneCall("execute").onObject(command);
	mock().setData("string passing to respond", "responding_string");
	server->executeGameCommand("command", "parameters", buffer, buffer_size);
	STRCMP_EQUAL("responding_string", buffer);
}

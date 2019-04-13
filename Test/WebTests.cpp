//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

#include "WebTests.h"
#include "civetweb/CivetServer.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace srdev;

namespace
{
bool test = Test::addTestCase(make_shared<Test::WebTests>(), "WebTests");
}
namespace
{
	/* Exit flag for main loop */
	volatile bool exitNow = false;
}
/** Sender class. Can be used to send a command to the server.
 *  The receiver will acknowledge the command by calling Ack().
 *  \msc
 *    Sender,Receiver;
 *    Sender->Receiver [label="Command()", URL="\ref Receiver::Command()"];
 *    Sender<-Receiver [label="Ack()", URL="\ref Ack()", ID="1"];
 *  \endmsc
 */
srdev::TestResult srdev::Test::WebTests::runTest()
{
	if (AppArguments.find("WebTests") == AppArguments.end())
		return TestResult::Successful;

	std::vector<std::string> options = {
	"document_root", ".",
	"listening_ports", "8080"
	};

	CivetServer server(options);
	struct : public CivetHandler
	{
		bool handleGet(CivetServer* server, struct mg_connection* conn)
		{
			mg_printf(conn,
				"HTTP/1.1 200 OK\r\nContent-Type: "
				"text/plain\r\nConnection: close\r\n\r\n");
			mg_printf(conn, "Bye!\n");
			exitNow = true;
			return true;
		}
	} h_exit;
	server.addHandler("/exit", h_exit);

	while (!exitNow) {
		Sleep(1000);
	}


	return TestResult::Successful;
}

#include <iostream>
#include "log.h"

#include "uv.h"
#include "event_dispatcher.h"
#include "socket_tcp.h"
#include "my_server.h"



using namespace CHServer;
int main() {
	CHLog::Instance()->InitLog(".", "server");

	MyServer::Instance()->Initilize();

	MyServer::Instance()->Run();

	CHLog::Instance()->UninitLog();
}

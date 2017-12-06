#include <iostream>
#include "log.h"

#include "uv.h"
#include "event_dispatcher.h"
#include "socket_tcp.h"
#include "my_server.h"



using namespace CHServer;
int main() {
	CHLog::Instance()->InitLog(".", "server");
	MyServer *server = new MyServer();

	server->Initilize();

	server->Run();

	delete server;
	server = nullptr;

	CHLog::Instance()->UninitLog();
}

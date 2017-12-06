#include <iostream>
#include "log.h"

#include "uv.h"
#include "event_dispatcher.h"
#include "socket_tcp.h"
#include "my_server.h"



using namespace CHServer;
int main() {
	

	MyServer::Instance()->Initilize();

	MyServer::Instance()->Run();
}

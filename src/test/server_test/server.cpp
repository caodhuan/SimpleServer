#include <iostream>

#include "event_dispatcher.h"
#include "log.h"
#include "my_server.h"
#include "socket_tcp.h"

using namespace SimpleServer;
int main() {
  if (MyServer::Instance()->Initilize("./res/config.lua", "tServer")) {
    MyServer::Instance()->Run();
  }

  MyServer::Instance()->Finalize();
}

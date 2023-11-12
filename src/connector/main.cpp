#include "connector_server.h"

using namespace SimpleServer;

int main() {
  if (ConnectorServer::Instance()->Initilize("./res/config.lua", "tServer")) {
    ConnectorServer::Instance()->Run();
  }

  ConnectorServer::Instance()->Finalize();

  return 0;
}
#include "db_server.h"

using namespace SimpleServer;

int main() {
  if (DBServer::Instance()->Initilize()) {
    DBServer::Instance()->Run();
  }

  DBServer::Instance()->Finalize();

  return 0;
}
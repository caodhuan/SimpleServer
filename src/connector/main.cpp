#include "connector_server.h"

using namespace CHServer;

int main() {

	ConnectorServer::Instance()->Initilize();

	ConnectorServer::Instance()->Run();

	ConnectorServer::Instance()->Finalize();

	return 0;
}
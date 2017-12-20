#include "connector_server.h"

using namespace CHServer;

int main() {

	if (ConnectorServer::Instance()->Initilize()) {
		ConnectorServer::Instance()->Run();
	}

	ConnectorServer::Instance()->Finalize();

	return 0;
}
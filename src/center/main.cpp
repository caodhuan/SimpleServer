#include "center_server.h"

using namespace CHServer;
int main() {

	if (!CenterServer::Instance()->Initilize()) {
		return false;
	}

	CenterServer::Instance()->Run();

	CenterServer::Instance()->Finalize();

	return 0;
}
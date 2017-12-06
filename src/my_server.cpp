#include "my_server.h"

namespace CHServer {

	static MyServer server;

	bool MyServer::BeforeInitilize() {
		return true;
	}

	bool MyServer::AfterInitilize() {
		return true;
	}

	void MyServer::BeforeFinalize() {
	}

	void MyServer::AfterFinalize() {
	}

}
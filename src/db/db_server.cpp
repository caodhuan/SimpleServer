#include "db_server.h"

namespace CHServer {
	static DBServer server;

	bool DBServer::BeforeInitilize() {
		return true;
	}

	bool DBServer::AfterInitilize() {
		return true;
	}

	void DBServer::BeforeFinalize() {
	}

	void DBServer::AfterFinalize() {
	}

	Session* DBServer::CreateSession(SocketBase* socket) {
		return nullptr;
	}

}
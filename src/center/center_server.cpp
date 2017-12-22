#include "center_server.h"
#include "session.h"

namespace CHServer {

	static CenterServer server;

	bool CenterServer::BeforeInitilize() {
		return true;
	}

	bool CenterServer::AfterInitilize() {
		return true;
	}

	void CenterServer::BeforeFinalize() {
		
	}

	void CenterServer::AfterFinalize() {
		
	}

	CHServer::Session* CenterServer::CreateSession(SocketBase* socket) {
		return new Session(socket);
	}

}

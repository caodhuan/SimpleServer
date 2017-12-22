#include "center_server.h"
#include "server_session.h"

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
		return new ServerSession(socket);
	}

}

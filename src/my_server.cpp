#include "my_server.h"
#include "session.h"
#include "player_session.h"
#include "log.h"

namespace CHServer {

	static MyServer server;

	bool MyServer::BeforeInitilize() {
		CHLog::Instance()->InitLog(".", "server");

		return true;
	}

	bool MyServer::AfterInitilize() {
		return true;
	}

	void MyServer::BeforeFinalize() {
	}

	void MyServer::AfterFinalize() {
		CHLog::Instance()->UninitLog();
	}

	Session* MyServer::CreateSession(SocketBase* socket) {
		Session* session = new SessionPlayer(socket);
		AddSession(session);
		return session;
	}

	void MyServer::AddSession(Session* session) {
		m_sessions.insert(session);
	}

	void MyServer::RemoveSession(Session* session) {
		m_sessions.erase(session);
	}

}
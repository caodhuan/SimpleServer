#include "my_server.h"
#include "session.h"
#include "player_session.h"
#include "log.h"
#include "timer_factory.h"
#include "timer.h"

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
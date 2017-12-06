#include "server_base.h"
#include "event_dispatcher.h"
#include "session.h"
#include "log.h"
#include "socket_tcp.h"

#include "uv.h"

namespace CHServer {

	ServerBase::ServerBase()
		: m_dispatcher(NULL)
		, m_Server(NULL) {

	}

	ServerBase::~ServerBase() {

	}

	bool ServerBase::Initilize() {
		if (!BeforeInitilize()) {
			return false;
		}

		if (m_dispatcher) {
			CHERRORLOG("reinitilzed");
			return false;
		}

		m_dispatcher = new EventDispatcher();
		
		// 先手写吧，后面写一个配置模块
		m_Server = new SocketTCP(m_dispatcher);
		
		m_Server->SetCallback(nullptr, [&] {
			SocketTCP* tcpClient = m_Server->Accept();
			
			Session* session = new Session(tcpClient);

			session->InitSession();

			m_sessions.insert(session);

			CHDEBUGLOG("new client connected %s:%d", tcpClient->GetIP().c_str(), tcpClient->GetPort());
		}, 
			[&] {
			delete m_Server;
			m_Server = nullptr;
		});
		m_Server->Listen("0.0.0.0", 2345);

		return AfterInitilize();
	}

	void ServerBase::Finalize() {
		
		BeforeFinalize();

		for (auto item : m_sessions) {
			delete item;
		}
		m_sessions.clear();

		if (m_dispatcher) {
			delete m_dispatcher;
			m_dispatcher = NULL;
		}

		AfterFinalize();
	}

	void ServerBase::Run() {
		m_dispatcher->Run();
	}

}
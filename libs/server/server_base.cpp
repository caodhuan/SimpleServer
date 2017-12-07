#include "server_base.h"
#include "event_dispatcher.h"
#include "session.h"
#include "log.h"
#include "socket_tcp.h"

#include "uv.h"

namespace CHServer {
	template<>
	ServerBase* SingletonInheritable<ServerBase>::m_Instance = 0;

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

		m_Server->SetCallback(nullptr, [this] {
			SocketTCP* tcpClient = m_Server->Accept();

			Session* session = CreateSession(tcpClient);

			CHDEBUGLOG("new client connected %s:%d", tcpClient->GetIP().c_str(), tcpClient->GetPort());
		},
			[this] {
			// 这里目前没搞清楚为啥delete后，会造成this变量变得不可访问。
			SocketBase* tmp = m_Server;
			m_Server = nullptr;
			delete tmp;
		});
		m_Server->Listen("0.0.0.0", 2345);

		return AfterInitilize();
	}

	void ServerBase::Finalize() {

		BeforeFinalize();

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
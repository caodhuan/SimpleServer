#include "server_base.h"
#include "event_dispatcher.h"
#include "session.h"
#include "log.h"
#include "socket_tcp.h"

#include "uv.h"
#include "timer_factory.h"
#include "resource _manager.h"
#include "config.h"

namespace CHServer {
	template<>
	ServerBase* SingletonInheritable<ServerBase>::m_Instance = 0;

	ServerBase::ServerBase()
		: m_dispatcher(NULL)
		, m_Server(NULL) {

	}

	ServerBase::~ServerBase() {
	}

	bool ServerBase::Initilize(const char* path, const char* tableName) {
		if (!BeforeInitilize()) {
			return false;
		}

		if (m_dispatcher) {
			CHERRORLOG("reinitilzed");
			return false;
		}

		// 初始化脚本的搜索路径之类的
		if (!ResourceManager::Instance()->Initialize(path, tableName)) {
			CHERRORLOG("resource initialize failed!");
			return false;
		}

		Config* config = ResourceManager::Instance()->GetConfig();
		std::string logPath, logFileName;
		if (config && config->ReadString("sLogPath", logPath) && config->ReadString("sLogFileName", logFileName)) {
			CHLog::Instance()->InitLog(logPath.c_str(), logFileName.c_str());
		} else {
			CHERRORLOG("log initialize failed!");
			return false;
		}

		m_dispatcher = new EventDispatcher();

		TimerFactory::Instance()->InitTimerFactory(m_dispatcher);

		m_Server = new SocketTCP(m_dispatcher);

		m_Server->SetCallback(nullptr, [&] {
			SocketTCP* tcpClient = m_Server->Accept();

			Session* session = CreateSession(tcpClient);

			CHDEBUGLOG("new client connected %s:%d", tcpClient->GetIP().c_str(), tcpClient->GetPort());
		},
			[&] {
			// 这里目前没搞清楚为啥delete后，会造成this变量变得不可访问。
			SocketBase* tmp = m_Server;
			m_Server = nullptr;

			CHWARNINGLOG("before delete %ld", this);

			delete tmp;

			CHWARNINGLOG("after delete %ld", this);
		});

		int32_t internalPort;
		std::string internalIP;

		if (!config->ReadInt("sInternalPort", internalPort)) {
			CHERRORLOG("read internal port failed!");
			return false;
		}

		if (!config->ReadString("sInternalIP", internalIP)) {
			CHERRORLOG("read internal ip failed!");
			return false;
		}

		m_Server->Listen(internalIP.c_str(), internalPort);

		return AfterInitilize();
	}

	void ServerBase::Finalize() {

		BeforeFinalize();

		if (m_dispatcher) {
			delete m_dispatcher;
			m_dispatcher = NULL;
		}

		AfterFinalize();

		CHLog::Instance()->UninitLog();
	}

	void ServerBase::Run() {
		m_dispatcher->Run();
	}
}
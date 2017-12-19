#pragma once

#include <set>

#include "singleton.h"

namespace CHServer {
	class EventDispatcher;
	class Session;
	class SocketBase;
	class SocketTCP;
	
	// 一个服务器进程抽象
	class ServerBase : public SingletonInheritable<ServerBase> {
	public:
		ServerBase();
		virtual ~ServerBase();
	
	public:
		virtual bool BeforeInitilize() = 0;
		bool Initilize(const char* path = nullptr, const char* tableName = nullptr);
		virtual bool AfterInitilize() = 0;

		virtual void BeforeFinalize() = 0;
		void Finalize();
		virtual void AfterFinalize() = 0;

		void Run();

		virtual Session* CreateSession(SocketBase* socket) = 0;

	private:
		EventDispatcher* m_dispatcher;

		SocketTCP* m_Server;
	};
}

#pragma once

#include <set>

namespace CHServer {
	class EventDispatcher;
	class Session;

	// 一个服务器进程抽象
	class ServerBase {
	public:
		ServerBase();
		virtual ~ServerBase();
	public:
		virtual void BeforeInitilize();
		bool Initilize();
		virtual void AfterInitilize();

		virtual void BeforeFinalize();
		void Finalize();
		virtual void AfterFinalize();

	private:
		EventDispatcher* m_dispatcher;

		std::set<Session*> m_sessions;
	};
}

#pragma once

#include <vector>

namespace CHServer {
	class EventDispatcher;
	class SocketBase;
	class Channel;

	// 代表一个会话抽象
	class Session {
	public:
		Session(EventDispatcher* dispatcher);
		~Session();
	private:
		SocketBase* m_socket;
	};
}

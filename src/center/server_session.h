#pragma once
#include "session.h"

namespace CHServer {
	class CMD_REGISTER_SERVER;
	class CMD_UPDATE_SERVER_INFO;
	class CMD_QUERY_SERVER_INFO;

	class ServerSession : public Session {
	public:
		ServerSession(SocketBase* socket);
		~ServerSession();

	public:
		virtual bool ProcessPacket(const char* data, uint16_t len) override;

		virtual void OnSessionDisconnect() override;

	public:
		void OnRegisterServer(const CMD_REGISTER_SERVER* req);
		void OnUpdateServerInfo(const CMD_UPDATE_SERVER_INFO* req);
		void OnQueryServerInfo(const CMD_QUERY_SERVER_INFO* req);
	};
}
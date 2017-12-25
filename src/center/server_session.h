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
		bool ProcessPacket(const char* data, uint16_t len);

		virtual void OnSessionDisconnect() override;

	public:
		bool OnRegisterServer(const char* data, uint16_t len);
		bool OnUpdateServerInfo(const char* data, uint16_t len);
		bool OnQueryServerInfo(const char* data, uint16_t len);
	};
}
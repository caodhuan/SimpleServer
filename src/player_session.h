#pragma once
#include "session.h"


namespace CHServer {
	class SessionPlayer : public Session {
	public:
		SessionPlayer(SocketBase* socket);
		~SessionPlayer();
	public:
		virtual bool ProcessPacket(const char* data, uint16_t len) override;


		virtual void OnSessionDisconnect() override;

	};
}
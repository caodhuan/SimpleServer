#pragma once
#include "session.h"


namespace CHServer {
	class SessionPlayer : public Session {
	public:
		SessionPlayer(SocketBase* socket);
		~SessionPlayer();

	public:
		virtual void OnSessionDisconnect() override;
	};
}
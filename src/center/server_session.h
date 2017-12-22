#pragma once
#include "session.h"

namespace CHServer {
	class ServerSession : public Session {

	public:
		virtual bool ProcessPacket(const char* data, uint16_t len) override;

		virtual void OnSessionDisconnect() override;
	};
}
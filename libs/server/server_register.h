#pragma once

#include <stdint.h>
#include <string>
#include "session.h"

// 注册服务器
// 目前是注册到 center server 上

namespace CHServer {

	class Session;

	class ServerRegister : public Session {
	public:
		ServerRegister(SocketBase* socket);
		~ServerRegister();

	public:
		virtual void OnSessionDisconnect() override;

	public:
		void StartRegister();

	private:
		bool OnRegisterServerReturn(const char* data, uint16_t len);
		bool OnQureyServerInfoReturn(const char* data, uint16_t len);
		
	};
}
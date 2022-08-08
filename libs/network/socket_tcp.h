#pragma once
#include <string>

#include "socket_base.h"

namespace CHServer {
	class SocketTCP
		: public SocketBase {
	public:
		SocketTCP(EventDispatcher* dispatcher);
		virtual ~SocketTCP();

	public:

		// uv_handle_t* GetHandle() override;

		void Close() override;

		std::string GetIP() override;
		
		int32_t GetPort()  override;

		void Connect(const char* ip, int32_t port);

		void Listen(const char* ip, int32_t port);

		SocketTCP* Accept();
	public:
		void SetNodely(bool enable);

	private:
		// uv_tcp_t* m_handle;

		// uv_connect_t* m_connector;
	};
}
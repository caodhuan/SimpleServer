#include "socket_tcp.h"
#include "event_dispatcher.h"
#include "log.h"

namespace CHServer {

	SocketTCP::SocketTCP(EventDispatcher* dispatcher)
		: SocketBase(dispatcher)
		, m_handle(NULL)
		, m_connector(NULL) {

		m_handle = new uv_tcp_t();
		m_handle->data = this;
		uv_tcp_init(m_dispatcher->GetLoop(), m_handle);
	}

	SocketTCP::~SocketTCP() {
		CHDEBUGLOG("socket deleted");
		if (m_handle) {
			CHERRORLOG("m_handle is still alive on destructor!");
			delete m_handle;
			m_handle = NULL;
		}

		if (m_connector) {
			delete m_connector;
			m_connector = NULL;
		}

	}

	uv_handle_t* SocketTCP::GetHandle() {
		return (uv_handle_t*)m_handle;
	}

	void SocketTCP::Close() {
		if (!m_handle) {
			return;
		}

		uv_close((uv_handle_t*)m_handle, SocketBase::OnClosed);
		m_handle = NULL;
	}

	std::string SocketTCP::GetIP() {
		std::string result;
		sockaddr_in addr;
		int len = sizeof(addr);
		char ip[64] = { 0 };
		uv_tcp_getpeername(m_handle, (sockaddr*)&addr, &len);
		uv_ip4_name(&addr, (char*)ip, sizeof(addr));
		result = ip;

		return std::move(result);
	}

	int32_t SocketTCP::GetPort() {
		sockaddr_in addr;
		int len = sizeof(addr);
		char ip[64] = { 0 };
		uv_tcp_getpeername(m_handle, (sockaddr*)&addr, &len);

		return addr.sin_port;
	}

	void SocketTCP::Connect(const char* ip, int32_t port) {
		if (m_connector) {
			return;
		}

		m_connector = new uv_connect_t();
		m_connector->data = this;

		sockaddr_in addr;
		uv_ip4_addr(ip, port, &addr);

		uv_tcp_connect(m_connector, m_handle, (const sockaddr*)&addr, SocketBase::OnConnected);
	}

	void SocketTCP::Listen(const char* ip, int32_t port) {
		sockaddr_in addr;
		uv_ip4_addr(ip, port, &addr);

		int result = uv_tcp_bind(m_handle, (const struct sockaddr*) &addr, 0);
		if (result) {
			CHERRORLOG("bind error");
			return;
		}

		result = uv_listen((uv_stream_t*)m_handle, SOMAXCONN, SocketBase::OnNewConnection);

		if (result) {
			CHERRORLOG("listen error");
			Close();
			return;
		}

		CHWARNINGLOG("listen on %s, %d", ip, port);
	}

	SocketTCP* SocketTCP::Accept() {
		SocketTCP* tcp = new SocketTCP(m_dispatcher);
		uv_accept((uv_stream_t*)GetHandle(), (uv_stream_t*)tcp->GetHandle());
		uv_read_start((uv_stream_t*)tcp->GetHandle(), SocketBase::Allocator, SocketBase::OnReceived);

		return tcp;
	}

	void SocketTCP::SetNodely(bool enable) {
		uv_tcp_nodelay(m_handle, enable);
	}

}
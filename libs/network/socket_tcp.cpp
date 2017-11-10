#include "socket_tcp.h"
#include "event_dispatcher.h"

namespace CHServer {

	SocketTCP::SocketTCP(EventDispatcher* dispatcher)
		: SocketBase(dispatcher)
		, m_handle(NULL)
		, m_connector(NULL) {

	}

	SocketTCP::~SocketTCP() {
		if (m_handle) {
			Close();
		}
		if (m_connector) {
			delete m_connector;
			m_connector = NULL;
		}
	}

	bool SocketTCP::InitSocket() {
		if (m_handle) {
			return false;
		}

		m_handle = new uv_tcp_t();
		m_handle->data = this;
		uv_tcp_init(m_dispatcher->GetLoop(), m_handle);
		return true;
	}

	uv_handle_t* SocketTCP::GetHandle() {
		return (uv_handle_t*)m_handle;
	}

	void SocketTCP::Close() {	// 直接close会有什么影响？
		uv_close((uv_handle_t*)m_handle, NULL);
		delete m_handle;
		m_handle = NULL;
	}

	void SocketTCP::Connect(std::string ip, int32_t port) {
		if (m_connector) {
			
			return;
		}
		m_connector = new uv_connect_t();
		m_connector->data = this;

		sockaddr_in addr;
		uv_ip4_addr(ip.c_str(), port, &addr);

		uv_tcp_connect(m_connector, m_handle, (const sockaddr*)&addr, SocketBase::OnConnected);
	}

	void SocketTCP::SetNodely(bool enable) {
		uv_tcp_nodelay(m_handle, enable);
	}

}
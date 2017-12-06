#include "session.h"
#include "socket_tcp.h"
#include "commonprotobuf.h"
#include <functional>
#include "log.h"

#include "server_base.h"

namespace CHServer {

	Session::Session(SocketBase* socket)
		: m_socket(socket)
		, m_head() {

	}

	Session::~Session() {

	}

	void Session::InitSession() {
		m_socket->SetCallback(std::bind(&Session::OnConnected, this), std::bind(&Session::OnReceive, this), std::bind(&Session::OnClosed, this));
	}

	void Session::OnConnected() {
	}

	void Session::SendPacket(uint16_t cmd, const char* data, uint16_t len) {
		static PacketHeader header;
		header.cmd = cmd;
		header.totalLength = len + sizeof(header);

		header.HostToNetwork();

		this->Send((const char*)&header, sizeof(header));

		this->Send(data, len);
	}

	void Session::OnReceive() {
		CHERRORLOG("received");
		while (true) {
			int32_t dataLen = m_socket->GetDataLength();

			char* data = NULL;
			m_socket->ReadBuff(data);

			if (!m_head.totalLength) {
				if (dataLen < sizeof(m_head)) {
					break;
				}
				m_head = *(PacketHeader*)data;

			}
			m_head.NetworkToHost();

			if (m_head.totalLength > m_socket->GetDataLength()) {
				break;
			}

			if (!ProcessData(data + sizeof(m_head), m_head.totalLength - sizeof(m_head))) {
				// 关闭连接，打日志
				m_socket->Close();
			}

			m_socket->RemoveBuff(m_head.totalLength);
			m_head.totalLength = 0;
		}
	}

	void Session::OnClosed() {
		CHDEBUGLOG("session closed!");

		delete m_socket;
		m_socket = nullptr;

		OnSessionDisconnect();
	}

	bool Session::ProcessData(const char* data, uint16_t len) {
		const int32_t test = 1;
		switch (m_head.cmd) {

		case test:
		{
				  static PlayerInfo msg;
				  if (!msg.ParsePartialFromArray(data, len)) {
					  return false;
				  }
				  CHDEBUGLOG(msg.DebugString().c_str());
		}
			break;
		default:
			// 派发到子类
			return ProcessPacket(data, len);
		}
	}

	void Session::Close() {
		if (m_socket) {
			m_socket->Close();
		}

	}

	bool Session::IsClosed() {
		return m_socket ? m_socket->IsClosed() : true;
	}

	bool Session::ProcessPacket(const char* data, uint16_t len) {
		return true;
	}

	void Session::OnSessionDisconnect() {

	}

	void Session::Send(const char* data, uint16_t len) {
		m_socket->Send(data, len);
	}

}
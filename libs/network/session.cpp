#include "session.h"
#include "socket_tcp.h"
#include "commonprotobuf.h"

namespace CHServer {

	Session::Session(SocketBase* socket)
		: m_socket(socket)
		, m_head() {

	}

	Session::~Session() {

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

			if (!ProcessPacket(data + sizeof(m_head), m_head.totalLength - sizeof(m_head))) {
				// 关闭连接，打日志
				m_socket->Close();
			}

			m_socket->RemoveBuff(m_head.totalLength);
			m_head.totalLength = 0;
		}
	}

	bool Session::ProcessPacket(const char* data, uint16_t len) {
		switch (m_head.cmd) {

		default:
			static PlayerInfo msg;
			if (!msg.ParsePartialFromArray(data, len)) {
				return false;
			}

			break;
		}
		return true;
	}

	void Session::Send(const char* data, uint16_t len) {
		m_socket->Send(data, len);
	}

}
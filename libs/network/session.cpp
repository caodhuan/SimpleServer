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
		m_socket->SetCallback(std::bind(&Session::OnConnected, this), std::bind(&Session::OnReceive, this), std::bind(&Session::OnClosed, this));
	}

	Session::~Session() {

	}

	void Session::OnConnected() {
		OnSessionConnected();
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

		MESSAGEPROCEDURE procedure = FindProcedure(m_head.cmd);

		if (procedure) {
			return procedure(data, len);

		} else {
			CHERRORLOG("cant find message procedure: %d", m_head.cmd);
			return false;
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

	bool Session::RegisterProcedure(uint16_t cmd, MESSAGEPROCEDURE procedure) {
		MESSAGEPROCEDURE hadProcedure = FindProcedure(cmd);
		
		if (!hadProcedure) {
			m_procedures.insert(std::make_pair(cmd, procedure));

		} else {
			CHERRORLOG("duplicate message procedure cmd=%d", cmd);

			return false;

		}

		return true;
	}

	void Session::UnregisterProcedure(uint16_t cmd) {
		m_procedures.erase(cmd);
	}

	void Session::OnSessionConnected() {

	}

	void Session::OnSessionDisconnect() {

	}

	void Session::Send(const char* data, uint16_t len) {
		m_socket->Send(data, len);
	}

	MESSAGEPROCEDURE Session::FindProcedure(uint16_t cmd) {
		std::map<uint16_t, MESSAGEPROCEDURE>::iterator iter = m_procedures.find(m_head.cmd);
		if (iter != m_procedures.end()) {
			return iter->second;

		}
		return nullptr;
	}

}
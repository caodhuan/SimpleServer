#include "server_session.h"
#include "commonprotobuf.h"
#include "log.h"
#include "socket_base.h"

namespace CHServer {

	ServerSession::ServerSession(SocketBase* socket)
		: Session(socket) {

	}

	ServerSession::~ServerSession() {

	}

	bool ServerSession::ProcessPacket(const char* data, uint16_t len) {
		switch (m_head.cmd) {
		case UNKNOW:
			CHERRORLOG("unknow command %s", m_socket->GetIP());
			return false;
		case REGISTER_SERVER:
			{
				static CMD_REGISTER_SERVER req;
				if (!req.ParseFromArray(data, len))
				{
					return false;
				}
				OnRegisterServer(&req);
			}
			break;
		case UPDATE_SERVER_INFO:
			{
				static CMD_UPDATE_SERVER_INFO req;
				if (!req.ParseFromArray(data, len)) {
					return false;
				}
				OnUpdateServerInfo(&req);
			}
			break;
		case QUERY_SERVER_INFO:
			{
				static CMD_QUERY_SERVER_INFO req;
				if (!req.ParseFromArray(data, len)) {
					return false;
				}
				OnQueryServerInfo(&req);
			}
			break;
		default:
			break;
		}

		return true;
	}

	void ServerSession::OnSessionDisconnect() {
		CHWARNINGLOG("OnSessionDisconnect");
	}

	void ServerSession::OnRegisterServer(const CMD_REGISTER_SERVER* req) {
		CHWARNINGLOG("OnRegisterServer");
	}

	void ServerSession::OnUpdateServerInfo(const CMD_UPDATE_SERVER_INFO* req) {
		CHWARNINGLOG("OnUpdateServerInfo");
	}

	void ServerSession::OnQueryServerInfo(const CMD_QUERY_SERVER_INFO* req) {
		CHWARNINGLOG("OnQueryServerInfo");
	}

}
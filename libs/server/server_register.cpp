#include "server_register.h"
#include "common.h"
#include "socket_tcp.h"
#include "server_base.h"
#include "commonprotobuf.h"

namespace CHServer {

	ServerRegister::ServerRegister(SocketBase* socket)
		: Session(socket) {

		RegisterProcedure(REGISTER_SERVER_RETURN, std::bind(&ServerRegister::OnRegisterServerReturn, this, std::placeholders::_1, std::placeholders::_2));
		RegisterProcedure(QUERY_SERVER_INFO_RETURN, std::bind(&ServerRegister::OnQureyServerInfoReturn, this, std::placeholders::_1, std::placeholders::_2));
	}

	ServerRegister::~ServerRegister() {

	}

	void ServerRegister::OnSessionDisconnect() {
	}

	void ServerRegister::StartRegister() {
		
	}

	bool ServerRegister::OnRegisterServerReturn(const char* data, uint16_t len) {

		return true;
	}

	bool ServerRegister::OnQureyServerInfoReturn(const char* data, uint16_t len) {
		return true;
	}

}
#include "player_session.h"
#include "log.h"
#include "my_server.h"

namespace CHServer {

	SessionPlayer::SessionPlayer(SocketBase* socket)
		:Session(socket) {

	}

	SessionPlayer::~SessionPlayer() {

	}

	bool SessionPlayer::ProcessPacket(const char* data, uint16_t len) {
		CHDEBUGLOG("SessionPlayer::ProcessPacket");
		return true;
	}

	void SessionPlayer::OnSessionDisconnect() {
		((MyServer*)ServerBase::Instance())->RemoveSession(this);
		delete this;
	}
}
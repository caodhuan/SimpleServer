#include "player_session.h"

#include "log.h"
#include "my_server.h"

namespace SimpleServer {

SessionPlayer::SessionPlayer(SocketBase* socket) : Session(socket) {}

SessionPlayer::~SessionPlayer() {}

void SessionPlayer::OnSessionConnected() {}

void SessionPlayer::OnSessionDisconnect() {
  ((MyServer*)ServerBase::Instance())->RemoveSession(this);
  delete this;
}
}  // namespace SimpleServer
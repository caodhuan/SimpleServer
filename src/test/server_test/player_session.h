#pragma once
#include "session.h"

namespace SimpleServer {
class SessionPlayer : public Session {
 public:
  SessionPlayer(SocketBase* socket);
  ~SessionPlayer();

 public:
  virtual void OnSessionConnected() override;

  virtual void OnSessionDisconnect() override;
};
}  // namespace SimpleServer
#pragma once
#include "session.h"

namespace SimpleServer {
class CMD_REGISTER_SERVER;
class CMD_UPDATE_SERVER_INFO;
class CMD_QUERY_SERVER_INFO;

class ServerSession : public Session {
 public:
  ServerSession(SocketBase* socket);
  ~ServerSession();

 public:
  virtual void OnSessionConnected() override;

  virtual void OnSessionDisconnect() override;

 public:
  bool OnRegisterServer(const char* data, uint16_t len);
  bool OnUpdateServerInfo(const char* data, uint16_t len);
  bool OnQueryServerInfo(const char* data, uint16_t len);
};
}  // namespace SimpleServer
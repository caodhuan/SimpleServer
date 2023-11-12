#pragma once
#include <set>

#include "server_base.h"

namespace SimpleServer {

class MyServer : public ServerBase {
 public:
  virtual bool BeforeInitilize() override;

  virtual bool AfterInitilize() override;

  virtual void BeforeFinalize() override;

  virtual void AfterFinalize() override;

  virtual Session* CreateSession(SocketBase* socket) override;

 public:
  void AddSession(Session* session);

  void RemoveSession(Session* session);

 private:
  std::set<Session*> m_sessions;
};

}  // namespace SimpleServer
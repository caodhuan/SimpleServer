#pragma once
#include "server_base.h"

namespace SimpleServer {

class CenterServer : public ServerBase {
 public:
  virtual bool BeforeInitilize() override;

  virtual bool AfterInitilize() override;

  virtual void BeforeFinalize() override;

  virtual void AfterFinalize() override;

  virtual Session* CreateSession(SocketBase* socket) override;
};
}  // namespace SimpleServer
#pragma once

#include <boost/asio/io_context.hpp>
#include <set>

#include "singleton.h"

namespace SimpleServer {
class Session;
class SocketBase;

// 一个服务器进程抽象
class ServerBase : public SingletonInheritable<ServerBase> {
 public:
  ServerBase();
  virtual ~ServerBase();

 public:
  virtual bool BeforeInitilize() = 0;
  bool Initilize(const char* path = nullptr, const char* tableName = nullptr);
  virtual bool AfterInitilize() = 0;

  virtual void BeforeFinalize() = 0;
  void Finalize();
  virtual void AfterFinalize() = 0;

  void Run();

  virtual Session* CreateSession(SocketBase* socket) = 0;

 public:
  boost::asio::io_context& GetIOContext() { return m_io_context; }

 private:
  boost::asio::io_context m_io_context;
};
}  // namespace SimpleServer

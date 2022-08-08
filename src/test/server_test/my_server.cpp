#include "my_server.h"

#include "log.h"
#include "player_session.h"
#include "session.h"
#include "timer.h"
#include "timer_factory.h"

namespace CHServer {

static MyServer server;

bool MyServer::BeforeInitilize() { return true; }

bool MyServer::AfterInitilize() {
  TimerFactory::Instance()->AddTimer([] { warning_log("test message"); }, 10,
                                     0xffffffff);

  return true;
}

void MyServer::BeforeFinalize() {}

void MyServer::AfterFinalize() {}

Session* MyServer::CreateSession(SocketBase* socket) {
  Session* session = new SessionPlayer(socket);
  AddSession(session);
  return session;
}

void MyServer::AddSession(Session* session) { m_sessions.insert(session); }

void MyServer::RemoveSession(Session* session) { m_sessions.erase(session); }

}  // namespace CHServer
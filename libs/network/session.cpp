#include "session.h"

#include <functional>

#include "log.h"
#include "server_base.h"

namespace CHServer {

Session::Session(SocketBase* socket) : m_socket(socket), m_head() {}

Session::~Session() {}

void Session::OnConnected() { OnSessionConnected(); }

void Session::SendPacket(uint16_t cmd, const char* data, uint16_t len) {
  static PacketHeader header;
  header.cmd = cmd;
  header.totalLength = len + sizeof(header);

  header.HostToNetwork();

  this->Send((const char*)&header, sizeof(header));

  this->Send(data, len);
}

void Session::OnReceive() {
  error_log("received");
  while (true) {
    m_head.totalLength = 0;
  }
}

void Session::OnClosed() {
  debug_log("session closed!");

  delete m_socket;
  m_socket = nullptr;

  OnSessionDisconnect();
}

bool Session::ProcessData(const char* data, uint16_t len) {
  MESSAGEPROCEDURE procedure = FindProcedure(m_head.cmd);

  if (procedure) {
    return procedure(data, len);

  } else {
    error_log("cant find message procedure: %d", m_head.cmd);
    return false;
  }
}

void Session::Close() {
  if (m_socket) {
  }
}

bool Session::IsClosed() { return true; }

bool Session::RegisterProcedure(uint16_t cmd, MESSAGEPROCEDURE procedure) {
  MESSAGEPROCEDURE hadProcedure = FindProcedure(cmd);

  if (!hadProcedure) {
    m_procedures.insert(std::make_pair(cmd, procedure));

  } else {
    error_log("duplicate message procedure cmd=%d", cmd);

    return false;
  }

  return true;
}

void Session::UnregisterProcedure(uint16_t cmd) { m_procedures.erase(cmd); }

void Session::OnSessionConnected() {}

void Session::OnSessionDisconnect() {}

void Session::Send(const char* data, uint16_t len) {}

MESSAGEPROCEDURE Session::FindProcedure(uint16_t cmd) {
  std::map<uint16_t, MESSAGEPROCEDURE>::iterator iter =
      m_procedures.find(m_head.cmd);
  if (iter != m_procedures.end()) {
    return iter->second;
  }
  return nullptr;
}

}  // namespace CHServer
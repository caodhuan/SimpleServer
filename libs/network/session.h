#pragma once

#include <stdint.h>

#include <functional>
#include <map>
#include <vector>

#ifdef WIN32
#include <WinSock2.h>
#else
#include <netinet/in.h>
#endif

namespace SimpleServer {
class SocketBase;
class Channel;

typedef std::function<bool(const char*, uint16_t)> MESSAGEPROCEDURE;

struct PacketHeader {
  PacketHeader() : totalLength(0), cmd(0) {}

  void HostToNetwork() {
    totalLength = htons(totalLength);
    cmd = htons(cmd);
  }

  void NetworkToHost() {
    totalLength = ntohs(totalLength);
    cmd = ntohs(cmd);
  }

  uint16_t totalLength;
  uint16_t cmd;
};

// 代表一个会话抽象
class Session {
 public:
  Session(SocketBase* socket);
  virtual ~Session();

 public:
  // 发送数据
  void SendPacket(uint16_t cmd, const char* data, uint16_t len);

  SocketBase* GetSocket() { return m_socket; }

  void Close();

  bool IsClosed();

  bool RegisterProcedure(uint16_t cmd, MESSAGEPROCEDURE procedure);

  void UnregisterProcedure(uint16_t cmd);

 public:
  virtual void OnSessionConnected();

  virtual void OnSessionDisconnect();

 private:
  void OnConnected();

  // 处理接收数据
  void OnReceive();

  void OnClosed();

  bool ProcessData(const char* data, uint16_t len);

  void Send(const char* data, uint16_t len);

  MESSAGEPROCEDURE FindProcedure(uint16_t cmd);

 protected:
  SocketBase* m_socket;
  PacketHeader m_head;  // 包头

  std::map<uint16_t, MESSAGEPROCEDURE> m_procedures;
};
}  // namespace SimpleServer

#include "socket_base.h"

#include <cstring>
#include <iostream>
#include <thread>

#include "event_dispatcher.h"
#include "log.h"

namespace CHServer {

SocketBase::SocketBase(EventDispatcher* dispatcher)
    : m_sendBufferHead(&m_sendBuffer[0]),
      m_sendBuffIndex(0),
      m_sendingBufferHead(&m_sendBuffer[1]),
      m_dispatcher(dispatcher),
      m_isWriting(false),
      //m_shutDown(NULL),
      m_isShutDown(false) {
  for (int i = 0; i < SocketBase::MAX; i++) {
    m_callback[i] = nullptr;
  }

  //m_writer.data = this;
  m_receiveBuffer = new Buffer();
}

SocketBase::~SocketBase() {
  if (m_receiveBuffer) {
    delete m_receiveBuffer;
    m_receiveBuffer = NULL;
  }
}

void SocketBase::SetCallback(SocketCallback connected, SocketCallback received,
                             SocketCallback closed) {
  m_callback[CONNECTED] = connected;
  m_callback[RECEIVED] = received;
  m_callback[CLOSED] = closed;
}

bool SocketBase::IsClosed() { return true; }

bool SocketBase::IsShutDown() { return m_isShutDown; }

void SocketBase::ShutDown() {
  // if (m_isShutDown || m_shutDown) {
  // 	return;
  // }

  // m_shutDown = new uv_shutdown_t();

  // uv_shutdown(m_shutDown, (uv_stream_t*)GetHandle(), SocketBase::OnShutDown);
}

void SocketBase::Send(const char* data, uint16_t len) {
  // AppendSendData(data, len);
  // if (m_isWriting || IsClosed()) {
  // 	// 已经在发送了，下一次再发
  // 	return;
  // }
  // if (m_sendBuffIndex == 0) {
  // 	return;
  // }
  // m_isWriting = true;

  // uv_buf_t bufs;
  // static const int count = 1;
  // std::swap(m_sendBufferHead, m_sendingBufferHead);

  // bufs = uv_buf_init(&(*m_sendingBufferHead)[0], m_sendBuffIndex);

  // m_sendBuffIndex = 0;

  // uv_write(&m_writer, (uv_stream_t*)GetHandle(), &bufs, count,
  // SocketBase::OnSent);
}

int32_t SocketBase::GetDataLength() { return m_receiveBuffer->GetDataLength(); }

int32_t SocketBase::ReadBuff(char*& data) {
  data = m_receiveBuffer->GetDataPoint();

  return m_receiveBuffer->GetContinuesDatalength();
}

void SocketBase::RemoveBuff(int32_t len) { m_receiveBuffer->FreeData(len); }

void SocketBase::AppendSendData(const char* data, uint16_t len) {
  if (!data || len == 0) {
    return;
  }
  std::vector<char>& buffer = *m_sendBufferHead;
  if (buffer.size() - m_sendBuffIndex < len) {
    buffer.resize(len + m_sendBuffIndex);  //  CTODO:考虑内存对齐
  }
  memcpy(&buffer[m_sendBuffIndex], data, len);
  m_sendBuffIndex += len;
}

void SocketBase::SetShutDown() { m_isShutDown = true; }

}  // namespace CHServer
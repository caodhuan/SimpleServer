#include "event_dispatcher.h"

namespace CHServer {
EventDispatcher::EventDispatcher() {
  // m_loop = new uv_loop_t();
  // uv_loop_init(m_loop);
}

EventDispatcher::~EventDispatcher() {
  // if (m_loop) {
  // 	uv_loop_close(m_loop);
  // 	delete m_loop;
  // 	m_loop = nullptr;
  // }
}

void EventDispatcher::Run(int type) {
  m_io_context->run();
}

void EventDispatcher::BreakRun() {
  // CTODO: 需要关闭所有的handler
  // uv_stop(m_loop);
}

}  // namespace CHServer

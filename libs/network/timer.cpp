#include "timer.h"

#include "event_dispatcher.h"

// 时间管理
namespace CHServer {

Timer::Timer(uint64_t repeatedCount)
    : m_repeatedCount(repeatedCount), m_callback(nullptr) {
  // m_timer->data = this;
}

Timer::~Timer() {}

void Timer::OnTimer() {
  if (m_repeatedCount > 0) {
    --m_repeatedCount;

    if (m_repeatedCount == 0) {
      // uv_timer_stop(m_timer);
    }

    if (m_callback) {
      m_callback();
    }
  }
}

void Timer::SetCallback(std::function<void()> callback) {
  m_callback = callback;
}

}  // namespace CHServer
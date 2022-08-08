#include "timer_factory.h"

#include "event_dispatcher.h"
#include "log.h"
#include "timer.h"

namespace CHServer {

bool TimerFactory::InitTimerFactory(EventDispatcher* dispatcher) {
  m_dispatcher = dispatcher;

  return true;
}

Timer* TimerFactory::AddTimer(std::function<void()> callback, uint32_t seconds,
                              uint64_t repeatCount /*= 1*/) {
  // uv_timer_t* uvTime = new uv_timer_t;
  // uv_timer_init(m_dispatcher->GetLoop(), uvTime);

  // Timer* result = new Timer(uvTime, repeatCount);

  // result->SetCallback(callback);

  // uv_timer_start(uvTime, TimerFactory::OnTimerCallback, seconds, seconds);

  return nullptr;
}

void TimerFactory::DeleteTimer(Timer* timer) { delete timer; }
}  // namespace CHServer
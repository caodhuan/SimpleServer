#include "timer_factory.h"
#include "timer.h"
#include "uv.h"
#include "log.h"
#include "event_dispatcher.h"

namespace CHServer {

	bool TimerFactory::InitTimerFactory(EventDispatcher* dispatcher) {
		m_dispatcher = dispatcher;

		return true;
	}

	Timer* TimerFactory::AddTimer(std::function<void()> callback, uint32_t seconds, uint64_t repeatCount /*= 1*/) {
		uv_timer_t* uvTime = new uv_timer_t;
		uv_timer_init(m_dispatcher->GetLoop(), uvTime);

		Timer* result = new Timer(uvTime, seconds, repeatCount);

		result->SetCallback(callback);

		uv_timer_start(uvTime, TimerFactory::OnTimerCallback, seconds, repeatCount);

		return result;
	}

	void TimerFactory::DeleteTimer(Timer* timer) {
		int result = uv_timer_stop(timer->m_timer);
		if (result != 0) {
			CHERRORLOG("delete timer error %s", uv_strerror(result));
		}

		uv_close((uv_handle_t*)timer->m_timer, TimerFactory::OnClose);

		delete timer;
	}

	void TimerFactory::OnTimerCallback(uv_timer_t* handle) {
		Timer* instance = (Timer*)handle->data;
		instance->OnTimer();
	}

	void TimerFactory::OnClose(uv_handle_t* handle) {
		delete handle;
	}

}
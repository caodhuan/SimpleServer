#include "timer.h"
#include "event_dispatcher.h"

// 时间管理
namespace CHServer {

	Timer::Timer(uv_timer_t* timer, uint32_t timeout, uint64_t repeatedCount)
		: m_timer(timer)
		, m_timeout(timeout)
		, m_repeatedCount(repeatedCount)
		, m_callback(nullptr) {
		m_timer->data = this;
	}

	Timer::~Timer() {

	}

	void Timer::OnTimer() {
		if (m_callback) {
			m_callback();
		}
	}

	void Timer::SetCallback(std::function<void()> callback) {
		m_callback = callback;
	}

}
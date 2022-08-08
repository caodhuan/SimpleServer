#pragma once
#include <functional>
#include <stdint.h>

#include "singleton.h"

namespace CHServer {
	class Timer;
	class EventDispatcher;

	class TimerFactory : public Singleton<TimerFactory> {
	public:
		bool InitTimerFactory(EventDispatcher* dispatcher);

		Timer* AddTimer(std::function<void()> callback, uint32_t seconds, uint64_t repeatCount = 1);

		void DeleteTimer(Timer* timer);

		// TODO: 在这里将每个Timer都管理起来，退出后，全都终结掉
	private:
		// static void OnTimerCallback(uv_timer_t* handle);

		// static void OnClose(uv_handle_t* handle);

	private:
		EventDispatcher* m_dispatcher;
	};
}
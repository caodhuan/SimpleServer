#include "event_dispatcher.h"

namespace CHServer {
	EventDispatcher::EventDispatcher() {
		m_loop = new uv_loop_t();
		uv_loop_init(m_loop);
	}

	EventDispatcher::~EventDispatcher() {
		if (m_loop) {
			uv_loop_close(m_loop);
			delete m_loop;
			m_loop = nullptr;
		}
	}

	void EventDispatcher::Run(int type) {
		uv_run(m_loop, (uv_run_mode)type);
	}

	void EventDispatcher::BreakRun() {
		uv_stop(m_loop);
	}

}


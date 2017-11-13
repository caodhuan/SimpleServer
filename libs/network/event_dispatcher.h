#pragma once

#include "uv.h"

namespace CHServer {

	class EventDispatcher {
	public:
		EventDispatcher();
		~EventDispatcher();

		uv_loop_t* GetLoop() {
			return m_loop;
		}

		void Run(int type = uv_run_mode::UV_RUN_DEFAULT);
	private:
		uv_loop_t* m_loop;
	};
}
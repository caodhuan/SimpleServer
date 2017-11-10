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
	private:
		uv_loop_t* m_loop;
	};
}
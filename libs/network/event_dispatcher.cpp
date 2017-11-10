#include "event_dispatcher.h"

namespace CHServer {
	EventDispatcher::EventDispatcher()
	{
		m_loop = uv_loop_new();
	}

	EventDispatcher::~EventDispatcher()
	{
		if (m_loop)
		{
			uv_loop_close(m_loop);
			m_loop = nullptr;
		}
	}

}


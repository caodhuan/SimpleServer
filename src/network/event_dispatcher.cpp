#include "event_dispatcher.h"

namespace CHServer {
	EventDispatcher::EventDispatcher()
	{
		m_loop = uv_default_loop();
	}

	EventDispatcher::~EventDispatcher()
	{

	}

}


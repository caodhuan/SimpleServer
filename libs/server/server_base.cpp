#include "server_base.h"
#include "event_dispatcher.h"
#include "session.h"

namespace CHServer {

	ServerBase::ServerBase()
		: m_dispatcher(NULL) {

	}

	ServerBase::~ServerBase() {

	}

	bool ServerBase::Initilize() {
		if (!BeforeInitilize()) {
			return false;
		}

		m_dispatcher = new EventDispatcher();

		return AfterInitilize();
	}

	void ServerBase::Finalize() {
		
		BeforeFinalize();

		for (auto item : m_sessions) {
			delete item;
		}
		m_sessions.clear();

		if (m_dispatcher) {
			delete m_dispatcher;
			m_dispatcher = NULL;
		}

		AfterFinalize();
	}

}
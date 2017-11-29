#include "server_base.h"
#include "event_dispatcher.h"
#include "session.h"

namespace CHServer {

	ServerBase::ServerBase()
		: m_dispatcher(NULL) {

	}

	ServerBase::~ServerBase() {

	}

	void ServerBase::BeforeInitilize() {

	}

	bool ServerBase::Initilize() {
		m_dispatcher = new EventDispatcher();

		return true;
	}

	void ServerBase::AfterInitilize() {

	}

	void ServerBase::Finalize() {
		for (auto item : m_sessions) {
			delete item;
		}
		m_sessions.clear();

		if (m_dispatcher) {
			delete m_dispatcher;
			m_dispatcher = NULL;
		}
	}

}
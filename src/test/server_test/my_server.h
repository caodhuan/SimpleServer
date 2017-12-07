#pragma once
#include "server_base.h"
#include <set>

namespace CHServer {

class MyServer : public ServerBase {
public:
	virtual bool BeforeInitilize() override;

	virtual bool AfterInitilize() override;

	virtual void BeforeFinalize() override;

	virtual void AfterFinalize() override;

	virtual Session* CreateSession(SocketBase* socket) override;

public:
	void AddSession(Session* session);

	void RemoveSession(Session* session);

private:
	std::set<Session*> m_sessions;
};

}
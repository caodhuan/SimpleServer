#include "connector_server.h"

namespace SimpleServer {
static ConnectorServer server;
bool ConnectorServer::BeforeInitilize() { return true; }

bool ConnectorServer::AfterInitilize() { return true; }

void ConnectorServer::BeforeFinalize() {}

void ConnectorServer::AfterFinalize() {}

Session* ConnectorServer::CreateSession(SocketBase* socket) { return nullptr; }

}  // namespace SimpleServer
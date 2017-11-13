#include "log.h"

#include "uv.h"
#include "event_dispatcher.h"
#include "socket_tcp.h"

using namespace CHServer;
int main() {
	CHLog::Instance()->InitLog(".", "ch");
	EventDispatcher* dispatcher = new EventDispatcher();
	SocketTCP* server = new SocketTCP(dispatcher);

	server->SetCallback([&] {
		
		CHEWARNINGLOG("do nothing");
	}, [&] {
		
		SocketTCP* client = new SocketTCP(dispatcher);

		client->SetCallback([=] {
			CHEWARNINGLOG("client connected...");
			
		}, [=] {
			char msg[] = "12312312";
			CHEWARNINGLOG("client received...");
			client->Send(msg, sizeof(msg));
		});
		uv_accept((uv_stream_t*)server->GetHandle(), (uv_stream_t*)client->GetHandle());
		uv_read_start((uv_stream_t*)client->GetHandle(), SocketBase::Allocator, SocketBase::OnReceived);
	});

	server->Listen("127.0.0.1", 2345);

	dispatcher->Run();

	CHLog::Instance()->UninitLog();
}
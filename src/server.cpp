#include "log.h"

#include "uv.h"
#include "event_dispatcher.h"
#include "socket_tcp.h"

#include <iostream>

using namespace CHServer;
int main() {
	CHLog::Instance()->InitLog(".", "server");
	EventDispatcher* dispatcher = new EventDispatcher();
	SocketTCP* server = new SocketTCP(dispatcher);
	static int number = 0;
	server->SetCallback([&] {
		
		CHWARNINGLOG("do nothing");
	}, [&] {
		std::cout << ++number << "conneted" << std::endl;
		SocketTCP* client = new SocketTCP(dispatcher);

// 		client->SetCallback([=] {
// 			CHEWARNINGLOG("client connected...");
// 			
// 		}, [=] {
// 			char msg[] = "12312312";
// 			client->Send(msg, sizeof(msg));
// 		});
		uv_accept((uv_stream_t*)server->GetHandle(), (uv_stream_t*)client->GetHandle());
		client->Close();
		//uv_read_start((uv_stream_t*)client->GetHandle(), SocketBase::Allocator, SocketBase::OnReceived);
	});

	server->Listen("0.0.0.0", 2345);

	dispatcher->Run();

	server->Close();

	CHLog::Instance()->UninitLog();
}

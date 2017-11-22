#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif


#include <iostream>
#include <string>

#include "event_dispatcher.h"

#include "redis_async.h"

#include "hiredis.h"

#include "log.h"

#ifdef WIN32
extern"C" {
#include "msvs\deps\ae.h"
}

#endif // WIN32


using namespace std;
using namespace CHServer;

void RedisAsyncTest() {

#ifdef WIN32
	aeCreateEventLoop(std::thread::hardware_concurrency());
#endif // WIN32

	EventDispatcher dispatcher;

	RedisAsync redisAsync;
	redisAsync.Connect("192.168.143.89", 6379, &dispatcher);

	redisAsync.AsyncCommand([&](RedisAsync*, void* r) -> void {
		redisReply* reply = (redisReply*)r;
		std::cout << "this thread = " << std::this_thread::get_id() << "  reply =" << reply->str << std::endl;
	}, "SET KEY 1234");

	redisAsync.AsyncCommand([&](RedisAsync*, void* r) -> void {
		redisReply* reply = (redisReply*)r;
		std::cout << "this thread = " << std::this_thread::get_id() << "  reply =" << reply->str << std::endl;
	}, "GET KEY");

	std::cout << "this thread = " << std::this_thread::get_id() << std::endl;
	dispatcher.Run();
}

int main() {
#ifdef WIN32
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif
	CHLog::Instance()->InitLog(".", "redistest");

	//redisContext *c = redisConnect("192.168.143.89", 6379);
	//if (c == NULL || c->err) {
	//	if (c) {
	//		printf("Error: %s\n", c->errstr);
	//		// handle error
	//	} else {
	//		printf("Can't allocate redis context\n");
	//	}
	//} else {
	//	redisReply*  reply = (redisReply*)redisCommand(c, "set a b");

	//	cout << reply->str << endl;
	//	reply = (redisReply*)redisCommand(c, "get a ");
	//	cout << reply->str << endl;
	//}

	RedisAsyncTest();

	CHLog::Instance()->UninitLog();
}
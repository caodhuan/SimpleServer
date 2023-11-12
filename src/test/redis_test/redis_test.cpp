#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif

#include <iostream>
#include <string>

#include "event_dispatcher.h"
#include "hiredis.h"
#include "log.h"
#include "redis_async.h"

#ifdef WIN32
extern "C" {
#include "msvs\deps\ae.h"
}

#endif  // WIN32
#include "redis_factory.h"

using namespace std;
using namespace SimpleServer;

EventDispatcher* dispatcher = new EventDispatcher();
void MainExecuate(RedisAsync* redisAsync, void* r) {
  // 	redisReply* reply = (redisReply*)r;
  // 	std::cout << "MainExecuate this thread = " << std::this_thread::get_id()
  // << "  reply =" << reply->str << std::endl;
  //
  // 	string command;
  // 	std::getline(std::cin, command);
  // 	redisAsync->Command(MainExecuate, command.c_str());
  //
  // 	std::cout << "MainExecuate this thread = " << std::this_thread::get_id()
  // << std::endl;

  // std::this_thread::sleep_for(2s);
  // dispatcher->BreakRun();
  RedisFactory::Instance()->DeleteRedisAsync(redisAsync);
}

void RedisAsyncTest() {
  RedisAsync* redis = RedisFactory::Instance()->CreateRedisAsync();

#ifdef WIN32
  aeCreateEventLoop(std::thread::hardware_concurrency());
#endif  // WIN32

  redis->Connect("192.168.143.89", 6379, dispatcher);

  redis->Command(MainExecuate, "SET KEY 1234");

  std::cout << "this thread = " << std::this_thread::get_id() << std::endl;

  dispatcher->Run();
}

// int main() {
// #ifdef WIN32
// 	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
// 	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
// #endif
// 	CHLog::Instance()->InitLog(".", "redistest");
//
// 	//redisContext *c = redisConnect("192.168.143.89", 6379);
// 	//if (c == NULL || c->err) {
// 	//	if (c) {
// 	//		printf("Error: %s\n", c->errstr);
// 	//		// handle error
// 	//	} else {
// 	//		printf("Can't allocate redis context\n");
// 	//	}
// 	//} else {
// 	//	redisReply*  reply = (redisReply*)redisCommand(c, "set a b");
//
// 	//	cout << reply->str << endl;
// 	//	reply = (redisReply*)redisCommand(c, "get a ");
// 	//	cout << reply->str << endl;
// 	//}
//
// 	RedisAsyncTest();
//
// 	CHLog::Instance()->UninitLog();
//
// 	char* tes = new char[11000];
// 	delete dispatcher;
//
// }

struct Compose {
  Compose() : sss(19) {}

  ~Compose() {}

  void DoTest(std::function<void(void)> test) { test(); }

  int sss;
};
struct Test {
  Compose* a;

  Test() : a(new Compose()) {}

  void InitTest() {
    a->DoTest([this] {
      delete a;
      a = nullptr;
    });
  }
};

int main() {
  Test* t = new Test;
  t->InitTest();
}
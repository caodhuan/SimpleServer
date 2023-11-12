#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif

#include <string.h>

#include <iostream>

#include "event_dispatcher.h"
#include "log.h"
#include "mysql.h"
#include "session.h"
#include "socket_tcp.h"
#include "ss/common.pb.h"
using namespace std;
using namespace SimpleServer;

void TestMysql() {
  cout << "test mysql" << endl;
  MYSQL* mysql = mysql_init(NULL);

  if (mysql_real_connect(mysql, "127.0.0.1", "x", "x", "x", 3306, NULL, 0)) {
    if (mysql_select_db(mysql, "x") == 0) {
      char cmd[] = "select * from tbl_accounts";
      int nResult = mysql_real_query(mysql, cmd, strlen(cmd));
      if (nResult == 0) {
        MYSQL_RES* res = mysql_store_result(mysql);
        cout << res->row_count << endl;
      } else {
        cout << "error" << endl;
      }
    }
  }

  mysql_close(mysql);
}

void TestLibuv() {
  EventDispatcher* dispatcher = new EventDispatcher();
  SocketTCP* client = new SocketTCP(dispatcher);
  bool readOnce = false;
  char msg[] = "12312312";
  std::string str;
  str.assign(msg);

  client->SetCallback(
      [&] {
        client->Send(msg, sizeof(msg));
        // client->Close();
      },
      [&]() -> void {
        int len = client->GetDataLength();
        char* ptr = NULL;

        if (!readOnce && len > 1025) {
          readOnce = true;
          client->RemoveBuff(1025);
        }
        int readLen = client->ReadBuff(ptr);

        std::string tmp;
        tmp.assign(ptr, readLen);
        error_log(tmp.c_str());
        //
        // 		if (readLen < len) {
        // 			client->RemoveBuff(readLen);
        // 			readLen = client->ReadBuff(ptr);
        // 			str.append(ptr, readLen);
        // 		}
        // 		client->RemoveBuff(readLen);

        // std::cout << str.c_str();

        client->Send(str.c_str(), str.size());
      },
      nullptr);

  // client->Connect("139.199.199.121", 2345);
  client->Connect("127.0.0.1", 2345);
  dispatcher->Run();
}

void TestLibuv100000() {
  EventDispatcher* dispatcher = new EventDispatcher();

  for (int i = 0; i < 0; ++i) {
    SocketTCP* client = new SocketTCP(dispatcher);

    // 		client->SetCallback([&] {
    // 			std::cout << "connected" << std::endl;
    // 			client->Send(msg, sizeof(msg));
    // 		}, [&]()-> void {
    // 			int len = client->GetBuffLength();
    // 			char* ptr = NULL;
    //
    // 			if (!readOnce && len > 1025) {
    // 				readOnce = true;
    // 				client->RemoveBuff(1025);
    // 			}
    // 			int readLen = client->ReadBuff(ptr);
    //
    // 			std::string tmp;
    // 			tmp.assign(ptr, readLen);
    // 			error_log(tmp.c_str());
    // 			//
    // 			// 		if (readLen < len) {
    // 			// 			client->RemoveBuff(readLen);
    // 			// 			readLen = client->ReadBuff(ptr);
    // 			// 			str.append(ptr, readLen);
    // 			// 		}
    // 			// 		client->RemoveBuff(readLen);
    //
    // 			//std::cout << str.c_str();
    //
    // 			//client->Send(str.c_str(), str.size());
    // 		});

    // client->Connect("127.0.0.1", 2345);
    client->Connect("127.0.0.1", 2345);
  }
  std::cout << "connected" << std::endl;

  dispatcher->Run();

  delete dispatcher;
}

void TestSession() {
  EventDispatcher* dispatcher = new EventDispatcher();
  SocketTCP* tcp = new SocketTCP(dispatcher);
  Session* serve = new Session(tcp);
  tcp->SetCallback(
      [&] {
        ss::PlayerInfo info;
        info.set_name("test name");
        std::string data = info.SerializeAsString();
        serve->SendPacket(1, data.c_str(), data.size());
      },
      nullptr, nullptr);

  tcp->Connect("127.0.0.1", 2345);

  dispatcher->Run();
}
int main() {
#ifdef WIN32
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif
  CHLog::Instance()->InitLog(".", "ch");

  TestSession();
  // TestMysql();
  // TestLibuv();
  // TestLibuv100000();
  // char* test = new char[1000];
  //_CrtDumpMemoryLeaks();

  CHLog::Instance()->UninitLog();
}
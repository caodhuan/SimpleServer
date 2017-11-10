#include "socket_tcp.h"
#include "event_dispatcher.h"

#include "uv.h"
#include "mysql.h"

#include <iostream>
#include <string.h>


using namespace std;
using namespace CHServer;

void TestMysql() {
	cout << "test mysql" << endl;
	MYSQL* mysql = mysql_init(NULL);

	if (mysql_real_connect(mysql, "127.0.0.1", "x", "x", "x", 3306, NULL, 0)) {
		if (mysql_select_db(mysql, "x") == 0)
		{

			char cmd[] = "select * from tbl_accounts";
			int nResult = mysql_real_query(mysql, cmd, strlen(cmd));
			if (nResult == 0)
			{
				MYSQL_RES* res = mysql_store_result(mysql);
				cout << res->row_count << endl;
			}
			else
			{
				cout << "error" << endl;
			}
		}
	}

}


void TestLibuv() {
	EventDispatcher* dispatcher = new EventDispatcher();
	SocketTCP* client = new SocketTCP(dispatcher);
	client->InitSocket();
	client->SetCallback([=] {
		char msg[] = "12312312";
		client->Send(msg, sizeof(msg));
	}, [=] ()-> void {
		int len = client->GetBuffLength();
		char* ptr = NULL;
		int readLen = client->ReadBuff(ptr);
		std::string str;
		str.assign(ptr, readLen);
		std::cout << str.c_str();
	});

	client->Connect("127.0.0.1", 2356);
	dispatcher->Run();
	
}

int main() {
	TestMysql();

	TestLibuv();

}
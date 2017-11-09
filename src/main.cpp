extern "C" {
#include "uv.h"
}

#include "mysql.h"

#include <iostream>
#include <string.h>

using namespace std;

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

static uv_timer_t timer_handle;

static void timer_cb(uv_timer_t* handle) {
	std::cout << "test" << std::endl;
	uv_stop(handle->loop);
}

void TestLibuv() {
	int r;
	uv_loop_t loop;

	uv_loop_init(&loop);

	uv_timer_init(&loop, &timer_handle);
	uv_timer_start(&timer_handle, timer_cb, 100, 100);

	uv_loop_close(&loop);

	uv_run(&loop, UV_RUN_DEFAULT);

	uv_close((uv_handle_t*)&timer_handle, NULL);
	r = uv_run(&loop, UV_RUN_DEFAULT);

	uv_loop_close(&loop);
}

int main() {
	TestMysql();

	TestLibuv();

}
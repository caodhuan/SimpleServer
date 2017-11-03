#include <iostream>

#include "mysql.h"
#include <string.h>

using namespace std;
int main() {
	cout << "test" << endl;
	MYSQL* mysql = mysql_init(NULL);

	if (mysql_real_connect(mysql, "127.0.0.1", "x", "x", "x", 3306, NULL, 0)) {
		if (mysql_select_db(mysql, "x") == 0)
		{

			char cmd[] = "select * from tbl_accounts";
			int nResult = mysql_real_query(mysql, cmd, strlen(cmd) );
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
#include <iostream>
#include <string>
#include "hiredis.h"


using namespace std;

int main() {
	redisContext *c = redisConnect("192.168.143.89", 6379);
	if (c == NULL || c->err) {
		if (c) {
			printf("Error: %s\n", c->errstr);
			// handle error
		} else {
			printf("Can't allocate redis context\n");
		}
	} else {
		redisReply*  reply =(redisReply*)redisCommand(c, "set a b");

		cout << reply->str << endl;
		reply = (redisReply*)redisCommand(c, "get a ");
		cout << reply->str << endl;
	}
}
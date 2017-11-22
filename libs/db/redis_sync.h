#pragma once
#include <stdint.h>

struct redisContext;

struct redisReply;

namespace CHServer {
	
	class RedisSync {
	public:
		RedisSync();
		~RedisSync();

	public:
		bool Connect(const char* ip, int32_t port);

		redisReply* Command(const char *format, ...);

		redisReply* Command(int argc, const char **argv, const size_t *argvlen);

	private:
		redisContext* m_context;
	};
}
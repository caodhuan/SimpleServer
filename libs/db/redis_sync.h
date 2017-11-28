#pragma once
#include <stdint.h>

struct redisContext;

struct redisReply;

namespace CHServer {

	class RedisSync {
		friend class RedisFactory;

	public:
		bool Connect(const char* ip, int32_t port);

		redisReply* Command(const char *format, ...);

		redisReply* Command(int argc, const char **argv, const uint64_t *argvlen);
	private:
		RedisSync();
		~RedisSync();
	private:
		redisContext* m_context;
	};
}
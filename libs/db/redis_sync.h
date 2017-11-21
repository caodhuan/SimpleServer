#pragma once

struct redisContext;

namespace CHServer {
	
	class RedisSync {
	public:
		RedisSync();
		~RedisSync();
	private:
		redisContext* m_context;
	};
}
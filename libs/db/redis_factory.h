#pragma once
#include "singleton.h"


namespace CHServer {
	class RedisAsync;
	class RedisSync;

	// 异步的redis需要new出来，不允许在栈上创建
	// 干脆做个统一的工厂方法了
	class RedisFactory : public Singleton<RedisFactory> {
	public:
		RedisAsync* CreateRedisAsync();
		RedisSync* CreateRedisSync();

		void DeleteRedisAsync(RedisAsync* redis);
		void DeleteRedisSync(RedisSync* redis);

	private:

	};
}
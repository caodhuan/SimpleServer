#include "redis_factory.h"

#include "redis_async.h"
#include "redis_sync.h"

namespace SimpleServer {

RedisAsync* RedisFactory::CreateRedisAsync() { return new RedisAsync(); }

RedisSync* RedisFactory::CreateRedisSync() { return new RedisSync(); }

void RedisFactory::DeleteRedisAsync(RedisAsync* redis) { delete redis; }

void RedisFactory::DeleteRedisSync(RedisSync* redis) { delete redis; }

}  // namespace SimpleServer
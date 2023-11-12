#include "redis_sync.h"

#include "hiredis.h"
#include "log.h"

namespace SimpleServer {

RedisSync::RedisSync() : m_context(nullptr) {}

RedisSync::~RedisSync() {
  if (m_context) {
    redisFree(m_context);
    m_context = NULL;
  }
}

bool RedisSync::Connect(const char* ip, int32_t port) {
  if (m_context) {
    error_log("already connected!");
    return false;
  }
  m_context = redisConnect("192.168.143.89", 6379);

  return true;
}

redisReply* RedisSync::Command(const char* format, ...) {
  va_list ap;
  va_start(ap, format);

  redisReply* reply = (redisReply*)redisCommand(m_context, format, ap);

  return reply;
}

redisReply* RedisSync::Command(int argc, const char** argv,
                               const uint64_t* argvlen) {
  redisReply* reply =
      (redisReply*)redisCommandArgv(m_context, argc, argv, argvlen);

  return reply;
}

}  // namespace SimpleServer
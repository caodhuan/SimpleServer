#include "redis_async.h"

#include "event_dispatcher.h"
#include "log.h"

extern "C" {
#include "async.h"
#include "hiredis.h"
}

#ifdef WIN32
#include "msvs\win32_interop\win32_rfdmap.h"
#endif

#include <functional>

namespace CHServer {
static int32_t CallbackIndex = 0;

RedisAsync::RedisAsync() : m_context(nullptr), m_events(0) {}

RedisAsync::~RedisAsync() {
  if (m_context) {
    redisAsyncFree(m_context);
    m_context = NULL;
  }

  // 在OnClose里delete m_poll
  // uv_close((uv_handle_t*)m_poll, RedisAsync::OnClose);
}

bool RedisAsync::Connect(const char* ip, const int32_t port,
                         EventDispatcher* dispatcher) {
  if (!dispatcher) {
    CHERRORLOG("dispatcher is null");
    return false;
  }

  m_context = redisAsyncConnect(ip, port);

  if (!m_context || m_context->err) {
    CHERRORLOG(m_context->errstr);
    return false;
  }

  m_context->ev.data = this;

  if (RedisAttach(m_context, dispatcher) != REDIS_OK) {
    CHERRORLOG("attach error!");
    return false;
  }

  redisAsyncSetConnectCallback(m_context, &RedisAsync::OnConnectCallback);

  redisAsyncSetDisconnectCallback(m_context, &RedisAsync::OnDisconnectCallback);

  return true;
}

void RedisAsync::Command(RedisAsyncCommandCallback callback, const char* format,
                         ...) {
  va_list ap;
  va_start(ap, format);

  redisAsyncCommand(m_context, RedisAsync::OnCmdCallback,
                    (void*)*(int*)&CallbackIndex, format, ap);

  AddCallback(CallbackIndex++, callback);
}

void RedisAsync::Command(RedisAsyncCommandCallback callback, int argc,
                         const char** argv, const uint64_t* argvlen) {
  redisAsyncCommandArgv(m_context, RedisAsync::OnCmdCallback,
                        (void*)*(int*)&CallbackIndex, argc, argv, argvlen);

  m_callbacks.insert(std::make_pair(CallbackIndex, callback));

  AddCallback(CallbackIndex++, callback);
}

void RedisAsync::AddCallback(int32_t key, RedisAsyncCommandCallback callback) {
  if (m_callbacks.find(key) != m_callbacks.end()) {
    CHERRORLOG("to many commands!");
  }

  m_callbacks.insert(std::make_pair(key, callback));
}

void RedisAsync::OnConnectCallback(const redisAsyncContext* c, int status) {
  CHDEBUGLOG("OnConnectCallback status = %d", status);
}

void RedisAsync::OnDisconnectCallback(const redisAsyncContext* c, int status) {
  CHDEBUGLOG("OnDisconnectCallback status = %d", status);
}

void RedisAsync::OnCmdCallback(redisAsyncContext* c, void* r,
                               void* privatedata) {
  RedisAsync* instance = (RedisAsync*)c->ev.data;

  auto callback =
      instance->m_callbacks.find((int32_t)(int64_t)(int32_t*)privatedata);
  if (callback != instance->m_callbacks.end()) {
    RedisAsyncCommandCallback func = callback->second;

    instance->m_callbacks.erase(callback);

    func(instance, r);
  }

  redisReply* reply = (redisReply*)r;
  CHWARNINGLOG("thread ID = %lu, result = %s", std::this_thread::get_id(),
               reply->str);
}

int RedisAsync::RedisAttach(redisAsyncContext* context,
                            EventDispatcher* dispatcher) {
  RedisAsync* instance = (RedisAsync*)context->ev.data;

  context->ev.addRead = RedisAsync::RedisAddRead;
  context->ev.delRead = RedisAsync::RedisDelRead;
  context->ev.addWrite = RedisAsync::RedisAddWrite;
  context->ev.delWrite = RedisAsync::RedisDelWrite;
  context->ev.cleanup = RedisAsync::RedisCleanup;
  // instance->m_poll->data = instance;
  int fd = context->c.fd;
#ifdef WIN32
  fd = (int32_t)RFDMap::getInstance().lookupSocket(context->c.fd);
#endif
  // if (uv_poll_init_socket(dispatcher->GetLoop(), instance->m_poll, fd) != 0)
  // {
  //   return REDIS_ERR;
  // }

  return REDIS_OK;
}

// void RedisAsync::RedisPoll(uv_poll_t* handle, int status, int events) {
//   RedisAsync* instance = (RedisAsync*)handle->data;

//   if (status != 0) {
//     return;
//   }

//   if (instance->m_context != NULL && (events & UV_READABLE)) {
//     redisAsyncHandleRead(instance->m_context);
//   }
//   if (instance->m_context != NULL && (events & UV_WRITABLE)) {
//     redisAsyncHandleWrite(instance->m_context);
//   }
// }

void RedisAsync::RedisAddRead(void* privateData) {
  RedisAsync* instance = (RedisAsync*)privateData;

  // instance->m_events |= UV_READABLE;

  // uv_poll_start(instance->m_poll, instance->m_events, RedisPoll);
}

void RedisAsync::RedisDelRead(void* privateData) {
  RedisAsync* instance = (RedisAsync*)privateData;

  // instance->m_events &= ~UV_READABLE;

  // if (instance->m_events) {
  //   uv_poll_start(instance->m_poll, instance->m_events, RedisPoll);
  // } else {
  //   uv_poll_stop(instance->m_poll);
  // }
}

void RedisAsync::RedisAddWrite(void* privateData) {
  RedisAsync* instance = (RedisAsync*)privateData;

  // instance->m_events |= UV_WRITABLE;

  // uv_poll_start(instance->m_poll, instance->m_events, RedisPoll);
}

void RedisAsync::RedisDelWrite(void* privateData) {
  RedisAsync* instance = (RedisAsync*)privateData;

  // instance->m_events &= ~UV_WRITABLE;

  // if (instance->m_events) {
  //   uv_poll_start(instance->m_poll, instance->m_events, RedisPoll);
  // } else {
  //   uv_poll_stop(instance->m_poll);
  // }
}

void RedisAsync::RedisCleanup(void* privateData) {
  // 需要做的清理操作
}

// void RedisAsync::OnClose(uv_handle_t* handle) { delete handle; }

}  // namespace CHServer
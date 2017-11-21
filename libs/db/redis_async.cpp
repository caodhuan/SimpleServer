#include "redis_async.h"

#include "log.h"
#include "event_dispatcher.h"
#include "uv.h"

extern "C" {
#include "hiredis.h"
#include "async.h"
}

#ifdef WIN32 
#include "msvs\win32_interop\win32_rfdmap.h"
#endif

#include <functional>


namespace CHServer {

	RedisAsync::RedisAsync()
		: m_context(nullptr)
		, m_events(0) {

	}

	RedisAsync::~RedisAsync() {
		if (m_context) {
			redisAsyncFree(m_context);
		}
	}

	void RedisAsync::Connect(const char* ip, const int32_t port, EventDispatcher* dispatcher) {
		if (!dispatcher) {
			CHERRORLOG("dispatcher is null");
			return;
		}

		m_context = redisAsyncConnect(ip, port);

		if (!m_context || m_context->err) {
			CHERRORLOG(m_context->errstr);
			return;
		}


		m_context->ev.data = this;

		RedisAttach(m_context, dispatcher);

		redisAsyncSetConnectCallback(m_context, &RedisAsync::OnConnectCallback);

		redisAsyncSetDisconnectCallback(m_context, &RedisAsync::OnDisconnectCallback);
	}

	void RedisAsync::AsyncCommand(const char* command) {
		redisAsyncCommand(m_context, RedisAsync::OnCmdCallback, NULL, command);
	}

	void RedisAsync::OnConnectCallback(const redisAsyncContext *c, int status) {
		CHDEBUGLOG("OnConnectCallback status = %d", status);
	}

	void RedisAsync::OnDisconnectCallback(const redisAsyncContext *c, int status) {
		CHDEBUGLOG("OnDisconnectCallback status = %d", status);
	}

	void RedisAsync::OnCmdCallback(redisAsyncContext *c, void *r, void *privatedata) {
		redisReply *reply = (redisReply*)r;
		RedisAsync* instance = (RedisAsync*)privatedata;


		CHWARNINGLOG(reply->str);

	}

	int RedisAsync::RedisAttach(redisAsyncContext* context, EventDispatcher* dispatcher) {

		RedisAsync* instance = (RedisAsync*)context->ev.data;

		context->ev.addRead = RedisAsync::RedisAddRead;
		context->ev.delRead = RedisAsync::RedisDelRead;
		context->ev.addWrite = RedisAsync::RedisAddWrite;
		context->ev.delWrite = RedisAsync::RedisDelWrite;
		context->ev.cleanup = RedisAsync::RedisCleanup;
		instance->m_poll.data = instance;
		int fd = context->c.fd;
#ifdef WIN32
		fd = RFDMap::getInstance().lookupSocket(context->c.fd);
#endif
		if (uv_poll_init_socket(dispatcher->GetLoop(), &instance->m_poll, fd) != 0) {
			return REDIS_ERR;
		}

		return REDIS_OK;
	}

	void RedisAsync::RedisPoll(uv_poll_t* handle, int status, int events) {
		RedisAsync* instance = (RedisAsync*)handle->data;

		if (status != 0) {
			return;
		}

		if (instance->m_context != NULL && (events & UV_READABLE)) {
			redisAsyncHandleRead(instance->m_context);
		}
		if (instance->m_context != NULL && (events & UV_WRITABLE)) {
			redisAsyncHandleWrite(instance->m_context);
		}
	}

	void RedisAsync::RedisAddRead(void* privateData) {
		RedisAsync* instance = (RedisAsync*)privateData;

		instance->m_events |= UV_READABLE;

		uv_poll_start(&instance->m_poll, instance->m_events, RedisPoll);
	}

	void RedisAsync::RedisDelRead(void* privateData) {
		RedisAsync* instance = (RedisAsync*)privateData;

		instance->m_events &= ~UV_READABLE;

		if (instance->m_events) {
			uv_poll_start(&instance->m_poll, instance->m_events, RedisPoll);
		} else {
			uv_poll_stop(&instance->m_poll);
		}
	}

	void RedisAsync::RedisAddWrite(void* privateData) {
		RedisAsync* instance = (RedisAsync*)privateData;

		instance->m_events |= UV_WRITABLE;

		uv_poll_start(&instance->m_poll, instance->m_events, RedisPoll);
	}

	void RedisAsync::RedisDelWrite(void* privateData) {
		RedisAsync* instance = (RedisAsync*)privateData;

		instance->m_events &= ~UV_WRITABLE;

		if (instance->m_events) {
			uv_poll_start(&instance->m_poll, instance->m_events, RedisPoll);
		} else {
			uv_poll_stop(&instance->m_poll);
		}
	}

	void RedisAsync::OnClose(uv_handle_t* handle) {

	}

	void RedisAsync::RedisCleanup(void* privateData) {
		RedisAsync* instance = (RedisAsync*)privateData;

		instance->m_context = NULL;
		uv_close((uv_handle_t*)&instance->m_poll, OnClose);
	}
}
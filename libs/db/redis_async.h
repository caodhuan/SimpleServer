#pragma once
#include "uv.h"

#include <stdint.h>


struct redisAsyncContext;

namespace CHServer {
	
	class EventDispatcher;

	class RedisAsync {
	public:
		RedisAsync();

		~RedisAsync();

	public:
		void Connect(const char* ip, const int32_t port, EventDispatcher* dispatcher);

		void AsyncCommand(const char *command);

	private:
		static void OnConnectCallback(const redisAsyncContext *c, int status);

		static void OnDisconnectCallback(const redisAsyncContext *c, int status);

		static void OnCmdCallback(redisAsyncContext *c, void *r, void *privatedata);

	private:
		static int RedisAttach(redisAsyncContext* context, EventDispatcher* dispatcher);
		static void RedisPoll(uv_poll_t* handle, int status, int events);
		static void RedisAddRead(void* privateData);
		static void RedisDelRead(void* privateData);
		static void RedisAddWrite(void* privateData);
		static void RedisDelWrite(void* privateData);
		static void OnClose(uv_handle_t* handle);
		static void RedisCleanup(void* privateData);

	private:
		redisAsyncContext* m_context;

		// 用来包装 event 相关的参数，参考hiredis/adapters/libuv.h
		uv_poll_t m_poll;
		int m_events;
	};
}
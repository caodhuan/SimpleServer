#pragma once
#include "uv.h"

#include <stdint.h>
#include <functional>
#include <map>


struct redisAsyncContext;

namespace CHServer {
	
	class EventDispatcher;

	class RedisAsync;

	typedef std::function<void(RedisAsync*, void* r)> RedisAsyncCommandCallback;

	class RedisAsync {
	public:
		RedisAsync();

		~RedisAsync();

	public:
		bool Connect(const char* ip, const int32_t port, EventDispatcher* dispatcher);

		void Command(RedisAsyncCommandCallback callback, const char *format, ...);

		void Command(RedisAsyncCommandCallback callback, int argc, const char **argv, const uint64_t *argvlen);
	private:
		void AddCallback(int32_t key, RedisAsyncCommandCallback callback);

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
		static void RedisCleanup(void* privateData);

	private:
		redisAsyncContext* m_context;

		// 用来包装 event 相关的参数，参考hiredis/adapters/libuv.h
		uv_poll_t m_poll;
		int m_events;

	private:
		std::map<int32_t, RedisAsyncCommandCallback> m_callbacks;
	};
}
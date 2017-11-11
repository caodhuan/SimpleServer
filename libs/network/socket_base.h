#pragma once

#include "uv.h"

#include <vector>
#include <functional>
#include <stdint.h>
namespace CHServer {
	class ScoketBase;
	class EventDispatcher;

	typedef std::function<void(void)> SocketCallback;

	// socket基类，封装通用的socekt操作
	class SocketBase {
	public:
		SocketBase(EventDispatcher* dispatcher);
		virtual ~SocketBase();

	public:
		virtual bool InitSocket() = 0;
		virtual uv_handle_t* GetHandle() = 0;
		virtual void Close() = 0;

	public:
		void SetCallback(SocketCallback connected,
			SocketCallback received);
		bool IsClose();

		void Send(const char* data, int32_t len);


		int32_t GetBuffLength();

		// read之后, buff依然存在，当确定不需要，调用RemoveBuff
		// 如果返回的读取字节数小于 GetBuffLength，那么RemoveBuff之后在读一次即可
		int32_t ReadBuff(char*& data);
		void RemoveBuff(int32_t len);

	private:
		void AppendSendData(const char* data, int32_t len);
		
	protected:

		static void OnNewConnection(uv_stream_t* handle, int status);

		static void Allocator(uv_handle_t* handle, size_t suggestedSize, uv_buf_t* buf);

		static void OnReceived(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf);

		static void OnSent(uv_write_t* handle, int status);

		static void OnConnected(uv_connect_t* handle, int status);

		static void OnClose(uv_handle_t* handle);

	protected:
		enum {
			CONNECTED = 0,
			RECEIVED = 1,
			MAX = 2,
		};
		static const int32_t SendBuffCount = 2;
		std::vector<char> m_receiveBuffer;
		int32_t m_receiveStartIndex;
		int32_t m_receiveIndex;

		std::vector<char> m_sendBuffer[SendBuffCount];
		std::vector<char>* m_sendBufferHead;
		int32_t m_sendBuffIndex;
		std::vector<char>* m_sendingBufferHead;

		SocketCallback m_callback[MAX];

		EventDispatcher* m_dispatcher;

		uv_write_t m_writer;
		bool m_isWriting;
	};

}
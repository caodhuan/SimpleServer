#pragma once

#include "uv.h"

#include <vector>
#include <functional>
#include <stdint.h>
#include <string>
#include "buffer.h"

namespace CHServer {
	class SocketBase;
	class EventDispatcher;

	typedef std::function<void(void)> SocketCallback;
	// socket基类，封装通用的socekt操作
	class SocketBase {
	public:
		SocketBase(EventDispatcher* dispatcher);
		virtual ~SocketBase();

	public:
		virtual uv_handle_t* GetHandle() = 0;
		virtual void Close() = 0;
		virtual std::string GetIP() = 0;
		virtual int32_t GetPort() = 0;
	public:
		void SetCallback(SocketCallback connected, SocketCallback received, SocketCallback closed);
		bool IsClosed();

		void Send(const char* data, uint16_t len);

		// 可以读取的字节数
		int32_t GetDataLength();

		// read之后, buff依然存在，当确定不需要，调用RemoveBuff
		// 如果返回的读取字节数小于 GetBuffLength，那么RemoveBuff之后在读一次即可
		int32_t ReadBuff(char*& data);
		void RemoveBuff(int32_t len);

	private:
		void AppendSendData(const char* data, uint16_t len);
		
	public:

		static void OnNewConnection(uv_stream_t* handle, int status);

		static void Allocator(uv_handle_t* handle, size_t suggestedSize, uv_buf_t* buf);

		static void OnReceived(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf);

		static void OnSent(uv_write_t* handle, int status);

		static void OnConnected(uv_connect_t* handle, int status);

		static void OnClosed(uv_handle_t* handle);

	protected:
		enum {
			CONNECTED = 0,
			RECEIVED = 1,
			CLOSED = 2,
			MAX,
		};
		static const int32_t SendBuffCount = 2;
		
		Buffer* m_receiveBuffer;

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
#pragma once

#include "uv.h"

#include <vector>
#include <functional>
#include <stdint.h>
namespace CHServer{
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

public:
	void SetCallback(SocketCallback connected, 
					 SocketCallback received);

	int32_t GetSignal() {
		return m_sigNum;
	}

	void Close();

	bool IsClose();
private:

	static void OnNewConnection(uv_stream_t* handle, int status);

	static void Allocator(uv_handle_t* handle, size_t suggestedSize, uv_buf_t* buf);

	static void OnReceived(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf);

	static void OnSent(uv_write_t* handle, int status);

	static void OnConnected(uv_connect_t* handle, int status);

	static void OnClose(uv_handle_t* handle);
	
private:
	enum {
		CONNECTED = 0,
		RECEIVED = 1,
		MAX = 2,
	};
	std::vector<char> m_ReceiveBuffer;
	uint32_t m_receiveIndex;
	std::vector<char> m_SendBUffer;
	uint32_t m_sendIndex;
	
	int32_t m_sigNum;

	uv_handle_t* m_handler;

	EventDispatcher* m_dispatcher;

	SocketCallback m_callback[MAX];
};

}
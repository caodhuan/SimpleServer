#pragma once

#include "uv.h"

#include <vector>
#include <stdint.h>
namespace CHServer{

// socket基类，封装通用的socekt操作
class SocketBase {
public:
	SocketBase();
	virtual ~SocketBase();

private:

	static void OnNewConnection(uv_stream_t* handle, int status);

	static void Allocator(uv_handle_t* handle, size_t suggestedSize, uv_buf_t* buf);

	static void OnRead(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf);

	static void OnSent(uv_write_t* handle, int status);

	static void OnConnected(uv_connect_t* handle, int status);

	static void OnClose(uv_handle_t* handle);

private:
	std::vector<char> m_ReceiveBuffer;
	uint32_t m_receiveIndex;
	std::vector<char> m_SendBUffer;
	uint32_t m_sendIndex;
	
	uv_handle_t* m_handler;
};

}
#include "socket_base.h"

namespace CHServer {


	SocketBase::SocketBase()
		: m_receiveIndex(0)
		, m_sendIndex(0)
	{

	}

	SocketBase::~SocketBase()
	{

	}

	void SocketBase::OnNewConnection(uv_stream_t* handle, int status)
	{

	}

	void SocketBase::Allocator(uv_handle_t* handle, size_t suggestedSize, uv_buf_t* buf)
	{
		SocketBase* socket = (SocketBase*)handle->data;
		uint32_t remainSize = socket->m_ReceiveBuffer.size() - socket->m_receiveIndex;
		if (remainSize < suggestedSize)
		{
			socket->m_ReceiveBuffer.resize(suggestedSize - remainSize);
		}
		buf->base = &socket->m_ReceiveBuffer[socket->m_receiveIndex];
	}

	void SocketBase::OnRead(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf)
	{

	}

	void SocketBase::OnSent(uv_write_t* handle, int status)
	{

	}

	void SocketBase::OnConnected(uv_connect_t* handle, int status)
	{

	}

	void SocketBase::OnClose(uv_handle_t* handle)
	{

	}

}
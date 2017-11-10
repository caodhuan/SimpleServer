#include "socket_base.h"
#include "event_dispatcher.h"

namespace CHServer {


	SocketBase::SocketBase(EventDispatcher* dispatcher)
		: m_receiveIndex(0)
		, m_sendIndex(0)
		, m_sigNum(0)
		, m_dispatcher(dispatcher)
		, m_handler(NULL)
		, m_callback{NULL}
	{

	}

	SocketBase::~SocketBase()
	{

	}

	void SocketBase::SetCallback(SocketCallback connected, SocketCallback received)
	{
		m_callback[CONNECTED] = connected;
		m_callback[RECEIVED] = received;
	}

	void SocketBase::Close()
	{
		uv_close(m_handler, NULL);
		m_handler = NULL;
	}

	bool SocketBase::IsClose()
	{
		return m_handler == NULL;
	}

	void SocketBase::OnNewConnection(uv_stream_t* handle, int status)
	{
		SocketBase* socket = (SocketBase*)handle->data;
		socket->m_callback[RECEIVED]();
	}

	void SocketBase::Allocator(uv_handle_t* handle, size_t suggestedSize, uv_buf_t* buf)
	{
		SocketBase* socket = (SocketBase*)handle->data;
		uint32_t remainSize = (uint32_t)socket->m_ReceiveBuffer.size() - socket->m_receiveIndex;
		if (remainSize < suggestedSize)
		{
			socket->m_ReceiveBuffer.resize(suggestedSize - remainSize);
		}
		buf->base = &socket->m_ReceiveBuffer[socket->m_receiveIndex];
	}

	void SocketBase::OnReceived(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf)
	{
		SocketBase* socket = (SocketBase*)handle->data;
		socket->m_callback[RECEIVED]();
	}

	void SocketBase::OnSent(uv_write_t* handle, int status)
	{
		SocketBase* socket = (SocketBase*)handle->data;

	}

	void SocketBase::OnConnected(uv_connect_t* handle, int status)
	{
		SocketBase* socket = (SocketBase*)handle->data;
		socket->m_callback[CONNECTED]();
	}

	void SocketBase::OnClose(uv_handle_t* handle)
	{
		SocketBase* socket = (SocketBase*)handle->data;
		socket->Close();
	}
}
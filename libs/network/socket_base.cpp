#include "socket_base.h"
#include "event_dispatcher.h"
#include "log.h"

#include<cstring>
#include <iostream>
#include <thread>


namespace CHServer {


	SocketBase::SocketBase(EventDispatcher* dispatcher)
		: m_sendBufferHead(&m_sendBuffer[0])
		, m_sendBuffIndex(0)
		, m_sendingBufferHead(&m_sendBuffer[1])
		, m_dispatcher(dispatcher)
		, m_isWriting(false) {
		for (int i = 0; i < SocketBase::MAX; i++) {
			m_callback[i] = nullptr;
		}

		m_writer.data = this;
		m_receiveBuffer = new Buffer();
	}

	SocketBase::~SocketBase() {
		if (m_receiveBuffer) {
			delete m_receiveBuffer;
			m_receiveBuffer = NULL;
		}
	}

	void SocketBase::SetCallback(SocketCallback connected, SocketCallback received, SocketCallback closed) {
		m_callback[CONNECTED] = connected;
		m_callback[RECEIVED] = received;
		m_callback[CLOSED] = closed;
	}

	bool SocketBase::IsClosed() {
		return GetHandle() == NULL;
	}

	void SocketBase::Send(const char* data, uint16_t len) {
		AppendSendData(data, len);
		if (m_isWriting || IsClosed()) {
			// 已经在发送了，下一次再发
			return;
		}
		if (m_sendBuffIndex == 0) {
			return;
		}
		m_isWriting = true;

		uv_buf_t bufs;
		static const int count = 1;
		std::swap(m_sendBufferHead, m_sendingBufferHead);

		bufs = uv_buf_init(&(*m_sendingBufferHead)[0], m_sendBuffIndex);

		m_sendBuffIndex = 0;

		uv_write(&m_writer, (uv_stream_t*)GetHandle(), &bufs, count, SocketBase::OnSent);

	}

	int32_t SocketBase::GetDataLength() {
		return m_receiveBuffer->GetDataLength();
	}

	int32_t SocketBase::ReadBuff(char*& data) {
		data = m_receiveBuffer->GetDataPoint();

		return m_receiveBuffer->GetContinuesDatalength();
	}

	void SocketBase::RemoveBuff(int32_t len) {
		m_receiveBuffer->FreeData(len);
	}

	void SocketBase::AppendSendData(const char* data, uint16_t len) {
		if (!data || len == 0) {
			return;
		}
		std::vector<char>& buffer = *m_sendBufferHead;
		if (buffer.size() - m_sendBuffIndex < len) {
			buffer.resize(len + m_sendBuffIndex); //  CTODO:考虑内存对齐
		}
		memcpy(&buffer[m_sendBuffIndex], data, len);
		m_sendBuffIndex += len;
	}

	void SocketBase::OnNewConnection(uv_stream_t* handle, int status) {
		SocketBase* socket = (SocketBase*)handle->data;
		if (socket->m_callback[RECEIVED]) {
			socket->m_callback[RECEIVED]();
		}
		/*
			初始化一个tcp
			然后 accept
			uv_accept
			*/
	}

	void SocketBase::Allocator(uv_handle_t* handle, size_t suggestedSize, uv_buf_t* buf) {
		// 由于suggestedSize 总是65536
		static const int SIZE = 1024;

		SocketBase* socket = (SocketBase*)handle->data;

		if (socket->m_receiveBuffer->GetFreeLength() == 0) {
			socket->m_receiveBuffer->AdjustLength(SIZE);
		}

		buf->base = socket->m_receiveBuffer->GetFreePoint();
		buf->len = socket->m_receiveBuffer->GetFreeLength();
	}

	void SocketBase::OnReceived(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf) {
		SocketBase* socket = (SocketBase*)handle->data;
		if (nread < 0) {
			CHERRORLOG("OnReceived nread = %s", uv_err_name(nread));
			socket->Close();
			return;
		}

		socket->m_receiveBuffer->FillData((int32_t)nread);

		if (socket->m_callback[RECEIVED]) {
			socket->m_callback[RECEIVED]();
		}
		CHDEBUGLOG("OnReceived thrad id = %d", std::this_thread::get_id());
	}

	void SocketBase::OnSent(uv_write_t* handle, int status) {
		SocketBase* socket = (SocketBase*)handle->data;
		socket->m_isWriting = false;
		socket->Send(NULL, 0);

		CHDEBUGLOG("OnSent");
	}

	void SocketBase::OnConnected(uv_connect_t* handle, int status) {
		SocketBase* socket = (SocketBase*)handle->data;
		if (socket->m_callback[CONNECTED]) {
			socket->m_callback[CONNECTED]();
		}
		uv_read_start(handle->handle, SocketBase::Allocator, SocketBase::OnReceived);
	}

	void SocketBase::OnClose(uv_handle_t* handle) {
		CHDEBUGLOG("SocketBase closed!!!");
		SocketBase* socket = (SocketBase*)handle->data;

		delete handle;
		handle = NULL;

		if (socket->m_callback[CLOSED]) {
			socket->m_callback[CLOSED]();
		} else {
			delete socket;
		}
	}
}
#pragma once

#include <stdint.h>
#include <vector>
#ifdef WIN32 
#include <WinSock2.h>
#else
#include <netinet/in.h>
#endif


namespace CHServer {
	class EventDispatcher;
	class SocketBase;
	class Channel;

	struct PacketHeader {
		PacketHeader()
			: totalLength(0)
			, cmd(0) {
		}

		void HostToNetwork() {
			totalLength = htons(totalLength);
			cmd = htons(cmd);
		}

		void NetworkToHost() {
			totalLength = ntohs(totalLength);
			cmd = ntohs(cmd);
		}

		uint16_t totalLength;
		uint16_t cmd;

	};

	// 代表一个会话抽象
	class Session {
	public:
		Session(SocketBase* socket);
		virtual ~Session();

	public:

		void InitSession();

		// 发送数据
		void SendPacket(uint16_t cmd, const char* data, uint16_t len);

		SocketBase* GetSocket() {
			return m_socket;
		}

		void Close();

		bool IsClosed();
	public:

		virtual bool ProcessPacket(const char* data, uint16_t len);

		virtual void OnSessionDisconnect();
	private:

		void OnConnected();

		// 处理接收数据
		void OnReceive();

		void OnClosed();

		bool ProcessData(const char* data, uint16_t len);

		void Send(const char* data, uint16_t len);
	private:
		SocketBase* m_socket;

		PacketHeader m_head; // 包头
	};
}

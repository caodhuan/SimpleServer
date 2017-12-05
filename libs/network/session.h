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
		// 发送数据
		void SendPacket(uint16_t cmd, const char* data, uint16_t len);

		// 处理接收数据
		void OnReceive();

		SocketBase* GetSocket() {
			return m_socket;
		}


	public:

		virtual bool ProcessPacket(const char* data, uint16_t len);
	private:
		void Send(const char* data, uint16_t len);
	private:
		SocketBase* m_socket;

		PacketHeader m_head; // 包头
	};
}

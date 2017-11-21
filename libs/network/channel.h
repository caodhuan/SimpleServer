#pragma once

namespace CHServer {
	// 解析数据包的基类
	class Channel {
	public:
		Channel();
		virtual ~Channel();
	public:
		virtual void OnActive();
		virtual void OnRead();
		virtual void OnWrite();
	};
}
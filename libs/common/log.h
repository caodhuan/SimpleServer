#pragma once
#include "singleton.h"
#include "blockingqueue.h"

namespace CHServer {
	// 日志相关
	// 线程安全的
	class CHLog
		: public SingletonBase<CHLog> {
	public:
		~CHLog();

	private:
		CHLog();
	private:
		BlockingQueue<std::string> m_logData; // 考虑换 T
	};
}
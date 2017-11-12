#pragma once
#include "singleton.h"

namespace CHServer {
	// 日志相关
	// 线程安全的
	class CHLog
		: public SingletonBase<CHLog> {
	public:
		~CHLog();

	private:
		CHLog();
	};
}
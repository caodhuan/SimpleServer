#include "redis_sync.h"

#include "hiredis.h"

namespace CHServer {

	RedisSync::RedisSync()
		: m_context(nullptr) {

	}

	RedisSync::~RedisSync() {
		if (m_context) {
			redisFree(m_context);
		}
	}

}
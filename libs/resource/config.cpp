#include "config.h"

namespace CHServer {
	
	Config::Config(const char* path) {
		m_state = luaL_newstate();

	}

	Config::~Config() {

	}

}
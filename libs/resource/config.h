#pragma once

#include <lua.hpp>

namespace CHServer {
	// 读取服务器配置
	class Config {
	public:
		Config(const char* path);
		~Config();
	public:

	private:
		// 每个配置文件，单独一个虚拟机
		lua_State* m_state;
	};
}
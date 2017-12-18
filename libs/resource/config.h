#pragma once

#include <lua.hpp>
#include <string>
#include <vector>
namespace CHServer {
	// 读取服务器配置
	// 一个Config代表一组配置，每组配置用table来表示
	// TODO: 索引表该如何读出？
	class Config {
	public:
		Config(const char* path, const char* tableName = "tConfig");
		~Config();
	private:
		Config(lua_State* state);
		Config();
	public:
		bool ReadInt(const char* name, int& result);
		
		bool ReadString(const char* name, std::string& result);

		// 这个Config与父Config共享一个虚拟机
		Config* ReadTable(const char* name);

	private:
		void AddTableName(const char* name);

		void PreparaStack(const char* fieldName);
		
		void RecoverStack();
	private:
		// 每个配置文件，单独一个虚拟机
		lua_State* m_state;
		bool m_haveParent;

		std::vector<std::string> m_tableName;

		int m_stackPos;
	};
}
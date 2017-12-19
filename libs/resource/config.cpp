#include "config.h"
#include "log.h"

namespace CHServer {

	static int Panic(lua_State* pState) {
		const char *msg = lua_tostring(pState, -1);

		CHERRORLOG(msg);

		return 0;
	}
	static int INVALID_STACK_POS = -1;

	Config::Config(const char* path, const char* tableName)
		: Config() {

		m_state = luaL_newstate();

		lua_atpanic(m_state, Panic);
		luaL_openlibs(m_state);

		luaL_dofile(m_state, path);

		AddTableName(tableName);
	}

	Config::Config(lua_State* state)
		: Config() {
		m_state = state;
		m_haveParent = true;
	}

	Config::Config()
		: m_state(nullptr)
		, m_haveParent(false)
		, m_stackPos(INVALID_STACK_POS) {

	}

	bool Config::Valid() {
		PreparaStack(nullptr);

		bool result = lua_istable(m_state, -1);
		
		RecoverStack();

		return result;
	}

	Config::~Config() {
		if (!m_haveParent && m_state) {
			lua_close(m_state);
			m_state = nullptr;
		}
	}

	bool Config::ReadInt(const char* name, int& result) {
		PreparaStack(name);

		if (!lua_isinteger(m_state, -1)) {
			return false;
		}

		result = lua_tointeger(m_state, -1);

		RecoverStack();

		return true;
	}

	bool Config::ReadString(const char* name, std::string& result) {
		PreparaStack(name);

		if (!lua_isstring(m_state, -1)) {
			return false;
		}

		size_t size = 0;
		const char* str = lua_tolstring(m_state, -1, &size);
		result.assign(str, size);

		RecoverStack();

		return true;
	}

	Config* Config::ReadTable(const char* name) {
		PreparaStack(name);
		if (!lua_istable(m_state, -1)) {
			return nullptr;
		}

		Config *config = new Config(m_state);

		config->AddTableName(name);

		RecoverStack();

		return config;
	}

	void Config::AddTableName(const char* name) {
		m_tableName.push_back(name);
	}

	void Config::PreparaStack(const char* fieldName) {
		m_stackPos = lua_gettop(m_state);

		lua_getglobal(m_state, m_tableName[0].c_str());

		int32_t deepth = m_tableName.size();
		for (int i = 1; i < deepth; ++i) {
			lua_pushstring(m_state, m_tableName[i].c_str());
			if (i < deepth - 1) {
				lua_rawget(m_state, -2);
			}
		}
		if (fieldName) {
			lua_pushstring(m_state, fieldName);
			lua_rawget(m_state, -2);
		}

	}

	void Config::RecoverStack() {
		if (m_stackPos != INVALID_STACK_POS) {
			lua_pop(m_state, lua_gettop(m_state) - m_stackPos);
		}

		m_stackPos = INVALID_STACK_POS;
	}

}
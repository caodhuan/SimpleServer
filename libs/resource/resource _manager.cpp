#include "resource _manager.h"
#include "config.h"

namespace CHServer {

	ResourceManager::ResourceManager()
		: m_config(nullptr) {

	}

	ResourceManager::~ResourceManager() {
		if (m_config) {
			delete m_config;
			m_config = nullptr;
		}
	}

	bool ResourceManager::Initialize() {
		// 找到路径
		std::string path = "./config.lua";
		m_config = new Config(path.c_str());

		return true;
	}

	void ResourceManager::Finalize() {

	}

}
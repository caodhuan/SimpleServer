#include "resource _manager.h"
#include "config.h"
#include "log.h"
#include "common.h"

namespace CHServer {

	ResourceManager::ResourceManager()
		: m_config(nullptr) {

	}

	ResourceManager::~ResourceManager() {
		SAFE_DELETE(m_config);
	}

	bool ResourceManager::Initialize(const char* path, const char* tableName) {
		if (path && tableName) {
			m_config = new Config(path, tableName);

			if (!m_config->Valid()) {
				CHERRORLOG("invalid server config!! path=%s, tableName=%s", path, tableName);
				return false;
			}
		} else {
			CHERRORLOG("attention! server config not initialize!!!");
		}
		
		return true;
	}

	void ResourceManager::Finalize() {

	}

}
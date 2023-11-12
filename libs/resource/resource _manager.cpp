#include "resource _manager.h"

#include "common.h"
#include "config.h"
#include "log.h"

namespace SimpleServer {

ResourceManager::ResourceManager() : m_config(nullptr) {}

ResourceManager::~ResourceManager() { SAFE_DELETE(m_config); }

bool ResourceManager::Initialize(const char* path, const char* tableName) {
  if (path && tableName) {
    m_config = new Config(path, tableName);

    if (!m_config->Valid()) {
      error_log("invalid server config!! path=%s, tableName=%s", path,
                tableName);
      return false;
    }
  } else {
    error_log("attention! server config not initialize!!!");
  }

  return true;
}

void ResourceManager::Finalize() {}

}  // namespace SimpleServer
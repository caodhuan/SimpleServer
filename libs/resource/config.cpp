#include "config.h"

#include "log.h"

namespace CHServer {

static int INVALID_STACK_POS = -1;

Config::Config(const char* path, const char* tableName) : Config() {
  AddTableName(tableName);
}

Config::Config() : m_haveParent(false) {}

bool Config::Valid() { return false; }

Config::~Config() {}

bool Config::ReadInt(const char* name, int& result) { return true; }

bool Config::ReadString(const char* name, std::string& result) { return true; }

Config* Config::ReadTable(const char* name) { return nullptr; }

void Config::AddTableName(const char* name) { m_tableName.push_back(name); }

void Config::PreparaStack(const char* fieldName) {}

void Config::RecoverStack() { m_stackPos = 0; }

bool Config::DoReadTable(const char* name, std::vector<int32_t>& values) {
  return true;
}

bool Config::DoReadTable(const char* name, std::vector<std::string>& values) {
  return true;
}

}  // namespace CHServer
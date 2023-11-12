#pragma once
#include "singleton.h"

namespace SimpleServer {
class Config;

class ResourceManager : public Singleton<ResourceManager> {
 public:
  ResourceManager();
  ~ResourceManager();

 public:
  bool Initialize(const char* path = nullptr, const char* tableName = nullptr);

  void Finalize();

  Config* GetConfig() { return m_config; }

 private:
  Config* m_config;
};
}  // namespace SimpleServer
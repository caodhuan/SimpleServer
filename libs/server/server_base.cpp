#include "server_base.h"

#include "config.h"
#include "log.h"
#include "resource _manager.h"
#include "session.h"

namespace SimpleServer {
template <>
ServerBase* SingletonInheritable<ServerBase>::m_Instance = 0;

ServerBase::ServerBase() : m_io_context() {}

ServerBase::~ServerBase() {}

bool ServerBase::Initilize(const char* path, const char* tableName) {
  if (!BeforeInitilize()) {
    return false;
  }

  // 初始化脚本的搜索路径之类的
  if (!ResourceManager::Instance()->Initialize(path, tableName)) {
    error_log("resource initialize failed!");
    return false;
  }

  Config* config = ResourceManager::Instance()->GetConfig();
  std::string logPath, logFileName;
  if (config && config->ReadString("sLogPath", logPath) &&
      config->ReadString("sLogFileName", logFileName)) {
    CHLog::Instance()->InitLog(logPath.c_str(), logFileName.c_str());
  } else {
    error_log("log initialize failed!");
    return false;
  }

  int32_t internalPort;
  std::string internalIP;

  if (!config->ReadInt("nInternalPort", internalPort)) {
    error_log("read internal port failed!");
    return false;
  }

  if (!config->ReadString("sInternalIP", internalIP)) {
    error_log("read internal ip failed!");
    return false;
  }

  std::vector<std::string> whiteList;
  if (!config->ReadVector("sWhiteList", whiteList)) {
    error_log("read white list failed!");
    return false;
  }

  return AfterInitilize();
}

void ServerBase::Finalize() {
  BeforeFinalize();

  AfterFinalize();
}

void ServerBase::Run() { m_io_context.run(); }

}  // namespace SimpleServer
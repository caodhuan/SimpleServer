#pragma once
#include "singleton.h"

namespace CHServer {

#define error_log(msg, ...)
#define debug_log(msg, ...)
#define warning_log(msg, ...)

enum log_level { trace, debug, info, warning, error, fatal };

// 日志相关
// 线程安全的
class CHLog : public Singleton<CHLog> {
 public:
  ~CHLog();

 public:
  bool InitLog(const char* path, const char* fileNamePrefix);

  void UpdateLogLevel(log_level level);

 private:
  friend class Singleton<CHLog>;

  CHLog();
};
}  // namespace CHServer
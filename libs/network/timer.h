#pragma once
#include <stdint.h>

#include <functional>

// 时间管理
namespace CHServer {

class Timer {
 public:
  static const int32_t SECOND = 1000;
  static const uint64_t FOREVER = 0xffffffff;

 private:
  friend class TimerFactory;
  Timer(uint64_t repeatedCount);
  ~Timer();

 private:
  void OnTimer();

  void SetCallback(std::function<void()> callback);

 private:
  // uv_timer_t* m_timer;
  uint64_t m_repeatedCount;
  std::function<void()> m_callback;
};
}  // namespace CHServer
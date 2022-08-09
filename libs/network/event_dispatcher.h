#pragma once
#include <boost/asio.hpp>

namespace CHServer {

class EventDispatcher {
 public:
  EventDispatcher();
  ~EventDispatcher();

  boost::asio::io_context* GetContext() { return m_io_context; }

  void Run(int type = 0 /*= uv_run_mode::UV_RUN_DEFAULT*/);

  // 这个方法要慎用呀，一不小心就内存泄露了
  // 需要将所有的handle全都释放，让其自然 break out
  void BreakRun();

 private:
  boost::asio::io_context* m_io_context;
};
}  // namespace CHServer
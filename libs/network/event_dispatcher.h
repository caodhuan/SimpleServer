#pragma once

namespace CHServer {

class EventDispatcher {
 public:
  EventDispatcher();
  ~EventDispatcher();

  // uv_loop_t* GetLoop() {
  // 	return m_loop;
  // }

  void Run(int type = 0 /*= uv_run_mode::UV_RUN_DEFAULT*/);

  // 这个方法要慎用呀，一不小心就内存泄露了
  // 需要将所有的handle全都释放，让其自然 break out
  void BreakRun();

 private:
  // uv_loop_t* m_loop;
};
}  // namespace CHServer
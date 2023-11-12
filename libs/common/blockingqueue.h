#pragma once
#include <condition_variable>
#include <deque>
#include <mutex>

namespace SimpleServer {
template <typename T>
class BlockingQueue {
 public:
  void Put(const T& element) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_data.push_back(element);
    m_condition.notify_one();
  }

  T Take() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_condition.wait(lock, [this](void) -> bool { return !m_data.empty(); });

    T front(m_data.front());
    m_data.pop_front();
    return front;
  }

  size_t Size() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_data.size();
  }

 private:
  std::mutex m_mutex;
  std::condition_variable m_condition;
  std::deque<T> m_data;
};
}  // namespace SimpleServer
#pragma once
#include "assert.h"

// 单例基类
namespace SimpleServer {

// 多线程安全的
template <typename T>
class Singleton {
 public:
  static T* Instance() {
    static T instance;  // no race condition, after c++11
    return &instance;
  }

 protected:
  Singleton() = default;
  virtual ~Singleton() = default;

 private:
  Singleton(const Singleton&) = delete;

  Singleton& operator=(const Singleton&) = delete;
};

// 需要自定义一个全局静态的变量！
template <typename T>
class SingletonInheritable {
 public:
  SingletonInheritable() {
    assert(m_Instance == nullptr);
    m_Instance = static_cast<T*>(this);
  }

  virtual ~SingletonInheritable() = default;

 public:
  static T* Instance() { return m_Instance; }

 protected:
  static T* m_Instance;
};
}  // namespace SimpleServer
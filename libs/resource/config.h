#pragma once

#include <stdint.h>

#include <string>
#include <vector>

namespace CHServer {
// 读取服务器配置
// 一个Config代表一组配置，每组配置用table来表示
// TODO: 索引表该如何读出？
// 需要搞一个圈套的字段配置，如果配置表里没有给出，就弄一个默认的值
class Config {
 public:
  Config(const char* path, const char* tableName = "tConfig");
  ~Config();

  bool Valid();

 private:
  Config();

 public:
  bool ReadInt(const char* name, int& result);

  bool ReadString(const char* name, std::string& result);

  // 这个Config与父Config共享一个虚拟机
  Config* ReadTable(const char* name);

  template <typename T>
  bool ReadVector(const char* name, std::vector<T>& values) {
    return DoReadTable(name, values);
  }

 private:
  void AddTableName(const char* name);

  void PreparaStack(const char* fieldName);

  void RecoverStack();

  bool DoReadTable(const char* name, std::vector<int32_t>& values);

  bool DoReadTable(const char* name, std::vector<std::string>& values);

 private:
  bool m_haveParent;

  std::vector<std::string> m_tableName;

  int m_stackPos;
};
}  // namespace CHServer
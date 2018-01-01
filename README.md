[![](https://travis-ci.org/caodhuan/CHServer.svg?branch=master)](https://travis-ci.org/caodhuan/CHServer) ![](https://img.shields.io/badge/language-cpp-brightgreen.svg)
# CHServer
一个 mmo 游戏服务器。
使用 libuv 做网络库，redis 做缓存，mysql 做数据落地，protobuf 做为数据传输、存储格式。
使用 lua 脚本作为服务器的配置文件。

## 构建
需要用 CMakeLists.txt 构建出来 protoc 工程后，再 cmake 运行一次。由于 protos/ 目录下的代码文件是由 protoc 工程解析生成的。
或者先 "cd 3rd/protobuf/cmake && cmake -Dprotobuf_BUILD_TESTS=OFF ."。
注意：都是64位
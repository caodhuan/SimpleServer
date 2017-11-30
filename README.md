[![](https://travis-ci.org/caodhuan/CHServer.svg?branch=master)](https://travis-ci.org/caodhuan/CHServer) ![](https://img.shields.io/badge/language-cpp-brightgreen.svg)
# CHServer
一个mmo游戏服务器

## 技术栈
使用libuv做网络库，redis做缓存，mysql做数据落地，protobuf做为数据传输、存储格式。目前还没想好要不要用脚本来开发逻辑- -#

## 构建
需要用CMakeLists.txt构建出来protoc工程后，再cmake运行一次。由于protos/目录下的代码文件是由protoc工程解析生成的。
或者先 cd 3rd/protobuf/cmake && cmake -Dprotobuf_BUILD_TESTS=OFF .
cmake_minimum_required(VERSION 3.2)

# 添加protobuf
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd/protobuf/src)

# hiredis
add_subdirectory(3rd/hiredis)

# leveldb
add_subdirectory(3rd/leveldb)
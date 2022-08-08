cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(CHServer)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++2a -g")
endif()

include(macros)
include(3rd)
include(libs)
include(servers)

group(test)
	addexec(client_test ${CMAKE_CURRENT_SOURCE_DIR}/src/test/client_test)

	addexec(server_test ${CMAKE_CURRENT_SOURCE_DIR}/src/test/server_test)

	addexec(redis_test ${CMAKE_CURRENT_SOURCE_DIR}/src/test/redis_test)

	addexec(test ${CMAKE_CURRENT_SOURCE_DIR}/src/test/test)
endgroup()

include_directories(${lib_path}/include)
include_directories(
	3rd/libuv/include
	3rd/libuv/src)

target_link_libraries(client_test server) 

target_link_libraries(server_test server) 

target_link_libraries(redis_test network db libprotobuf) 


if(UNIX)
	FIND_LIBRARY(gperftools profiler)
	if(gperftools)
		message(${gperftools})
		target_link_libraries(common ${gperftools} tcmalloc unwind)
	endif()
endif()

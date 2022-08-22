cmake_minimum_required(VERSION 3.2)

project(CHServer)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
add_definitions("-DBOOST_LOG_DYN_LINK -Wdeprecated-declarations")
if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++2a -g")
endif()

include(macros)
include(3rd)
include(libs)
#include(servers)

group(test)
	# addexec(client_test ${CMAKE_CURRENT_SOURCE_DIR}/src/test/client_test)

	# addexec(server_test ${CMAKE_CURRENT_SOURCE_DIR}/src/test/server_test)

	# addexec(redis_test ${CMAKE_CURRENT_SOURCE_DIR}/src/test/redis_test)

	addexec(test ${CMAKE_CURRENT_SOURCE_DIR}/src/test/test)
endgroup()

# target_link_libraries(client_test server) 

# target_link_libraries(server_test server) 

# target_link_libraries(redis_test network db protos) 
target_link_libraries(test common)
find_package(Boost 1.74.0 REQUIRED) 
if(Boost_FOUND)
	message("boost include and lib dirs: " ${Boost_INCLUDE_DIRS} ", " ${Boost_LIBRARY_DIRS})
	include_directories(${Boost_INCLUDE_DIRS})
endif()
target_link_libraries(test boost_timer boost_log pthread boost_thread boost_log_setup)
# if(UNIX)
# 	FIND_LIBRARY(gperftools profiler)
# 	if(gperftools)
# 		message("find gperftools: " ${gperftools})
# 		target_link_libraries(common ${gperftools} tcmalloc unwind)
# 	endif()
# endif()

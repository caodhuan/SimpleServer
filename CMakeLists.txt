cmake_minimum_required(VERSION 3.27)

project(SimpleServer)

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

	addexec(test ${CMAKE_CURRENT_SOURCE_DIR}/src/test/test)
endgroup()

# target_link_libraries(client_test server) 

# target_link_libraries(server_test server) 

target_link_libraries(test common)

# if(UNIX)
# 	FIND_LIBRARY(gperftools profiler)
# 	if(gperftools)
# 		message("find gperftools: " ${gperftools})
# 		target_link_libraries(common ${gperftools} tcmalloc unwind)
# 	endif()
# endif()

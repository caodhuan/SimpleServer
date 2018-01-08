cmake_minimum_required(VERSION 2.8)

project(CHServer)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 -g")
endif()

include(cotire)
include(macros)
include(3rd)
include(libs)
include(servers)

group(test)
	addexec(client_test ${CMAKE_CURRENT_SOURCE_DIR}/src/test/client_test)

	addexec(server_test ${CMAKE_CURRENT_SOURCE_DIR}/src/test/server_test)

	addexec(redis_test ${CMAKE_CURRENT_SOURCE_DIR}/src/test/redis_test)
endgroup()


if(WIN32)
	set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/3rd/mysql/win)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /Od /Oy- /MD ") #mysqlclient只能是MD  ？
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od /Oy- /MTd")	
	set(mysqlclient_lib 
		optimized ${lib_path}/lib/mysqlclient.lib
		debug ${lib_path}/lib/libmysql.lib)

	file(COPY ${lib_path}/lib/libmysql.dll DESTINATION ${CMAKE_WORKING_DIRECTORY}/)
	file(COPY ${lib_path}/lib/libmysql.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug)

	foreach(project ${group_proj})
		target_link_libraries(${project} ${mysqlclient_lib})

		target_link_libraries(${project} ws2_32.lib Psapi.lib IPHLPAPI.lib userenv.lib)

	endforeach()
	

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd/hiredis/windows)

else()
	set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/3rd/mysql/linux)

  	find_library(mysqlclient_lib mysqlclient)

    if(NOT mysqlclient_lib)
    	message(STATUS "mysqlclient NOT found")
		file(GLOB mysqlclient_lib ${lib_path}/lib/libmysqlclient.a)
    endif()

    foreach(project ${group_proj})
    	target_link_libraries(${project} ${mysqlclient_lib} pthread dl )
    endforeach()

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd/hiredis/linux)

endif()

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

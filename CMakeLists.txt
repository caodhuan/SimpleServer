cmake_minimum_required(VERSION 2.8)

project(CHServer)

include(cmake/macros.cmake)
include(cmake/3rd.cmake)
include(cmake/libs.cmake)
add_executable(MyTest ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(MyServerTest ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp)

add_executable(MyRedisTest ${CMAKE_CURRENT_SOURCE_DIR}/src/redis_test.cpp)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 -g")
target_link_libraries(MyTest libuv)
target_link_libraries(MyServerTest libuv)

if(WIN32)
	set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/3rd/mysql/win)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /Od /Oy- /MD ") #mysqlclient只能是MD  ？
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od /Oy- /MTd")	
	set(mysqlclient_lib 
		optimized ${lib_path}/lib/mysqlclient.lib
		debug ${lib_path}/lib/libmysql.lib)

	file(COPY ${lib_path}/lib/libmysql.dll DESTINATION ${CMAKE_WORKING_DIRECTORY}/)
	file(COPY ${lib_path}/lib/libmysql.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug)

	target_link_libraries(MyTest ${mysqlclient_lib})
	target_link_libraries(MyTest ws2_32.lib Psapi.lib IPHLPAPI.lib userenv.lib)
	target_link_libraries(MyServerTest ws2_32.lib Psapi.lib IPHLPAPI.lib userenv.lib)

	target_link_libraries(MyRedisTest ws2_32.lib Psapi.lib IPHLPAPI.lib userenv.lib)

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd/hiredis/win/hiredis/)

else()
	set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/3rd/mysql/linux)


  	find_library(mysqlclient_lib mysqlclient)
    if(NOT mysqlclient_lib)
    	message(STATUS "mysqlclient NOT found")
		file(GLOB mysqlclient_lib ${lib_path}/lib/libmysqlclient.a)
    endif()
	target_link_libraries(MyTest ${mysqlclient_lib} pthread dl )
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd/hiredis/linux/hiredis/)
endif()

include_directories(${lib_path}/include)
include_directories(
	3rd/libuv/include
	3rd/libuv/src)


target_link_libraries(network libuv common) 
target_link_libraries(db hiredis) 

target_link_libraries(MyTest network db common libprotobuf) 

target_link_libraries(MyServerTest network db common libprotobuf) 

target_link_libraries(MyRedisTest network  db common libprotobuf) 
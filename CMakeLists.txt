cmake_minimum_required(VERSION 2.8)

include(cmake/macros.cmake)

project(CHServer)

add_executable(MyTest ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(MyServerTest ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp)

add_subdirectory(3rd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")
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

else()
	set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/3rd/mysql/linux)


  	find_library(mysqlclient_lib mysqlclient)
    if(NOT mysqlclient_lib)
    	message(STATUS "mysqlclient NOT found")
		file(GLOB mysqlclient_lib ${lib_path}/lib/libmysqlclient.a)
    endif()
	target_link_libraries(MyTest ${mysqlclient_lib} pthread dl )
	
endif()

include_directories(${lib_path}/include)
include_directories(
	3rd/libuv/include
	3rd/libuv/src)


group(base)
	addlib(network ${CMAKE_CURRENT_SOURCE_DIR}/libs/network)
	addlib(db ${CMAKE_CURRENT_SOURCE_DIR}/libs/db)
	addlib(common ${CMAKE_CURRENT_SOURCE_DIR}/libs/common)
endgroup()

target_link_libraries(network libuv common) 

target_link_libraries(MyTest network db common ) 

target_link_libraries(MyServerTest network db common ) 


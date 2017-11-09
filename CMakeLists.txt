cmake_minimum_required(VERSION 2.8)

add_definitions(-DUNICODE -D_UNICODE)

# 可以使用文件夹
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(CHServer)

add_executable(MySQLTest ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_subdirectory(3rd)

if(WIN32)
	set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/3rd/mysql/win)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /Od /Oy- /MT ")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od /Oy- /MTd")	
	set(mysqlclient_lib 
		optimized ${lib_path}/lib/mysqlclient.lib
		debug ${lib_path}/lib/libmysql.lib)

	file(COPY ${lib_path}/lib/libmysql.dll DESTINATION ${CMAKE_WORKING_DIRECTORY}/)
	file(COPY ${lib_path}/lib/libmysql.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug)

	target_link_libraries(MySQLTest ${mysqlclient_lib} libuv)
	target_link_libraries(MySQLTest ws2_32.lib Psapi.lib IPHLPAPI.lib userenv.lib)

else()
	set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/3rd/mysql/linux)


  	find_library(mysqlclient_lib mysqlclient)
    if(NOT mysqlclient_lib)
		file(GLOB mysqlclient_lib ${lib_path}/lib/libmysqlclient.a)
    endif()
	target_link_libraries(MySQLTest ${mysqlclient_lib} libuv pthread dl )
endif()

include_directories(${lib_path}/include)
include_directories(
	3rd/libuv/include
	3rd/libuv/src)

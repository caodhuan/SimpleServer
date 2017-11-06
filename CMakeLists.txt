cmake_minimum_required(VERSION 2.8)

add_definitions(-DUNICODE -D_UNICODE)

# 可以使用文件夹
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(CHServer)

add_executable(MySQLTest ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

if(WIN32)
	set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/libs/win)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /Od /Oy- /MTd ")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od /Oy- /MTd")	
	file(GLOB mysqlclient_lib ${lib_path}/mysql/lib/mysqlclient.lib)
else()
	set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/libs/linux)


  	find_library(mysqlclient_lib mysqlclient)
    if(NOT mysqlclient_lib)
		file(GLOB mysqlclient_lib ${lib_path}/mysql/lib/libmysqlclient.a)
    endif()
	target_link_libraries(MySQLTest pthread dl)
endif()

include_directories(${lib_path}/mysql/include)


target_link_libraries(MySQLTest ${mysqlclient_lib})

add_subdirectory(3rd)
cmake_minimum_required(VERSION 2.8)

add_definitions(-DUNICODE -D_UNICODE)
project(CHServer)

add_executable(MySQLTest ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)


if(WIN32)
	set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/libs/win/)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /Od /Oy- /MTd ")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od /Oy- /MTd")
else()
	set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/libs/linux/)

	target_link_libraries(MySQLTest pthread dl)
endif()


file(GLOB mysqlib ${lib_path}/mysql/lib/mysqlclient.lib)

include_directories(${lib_path}/mysql/include)

target_link_libraries(MySQLTest ${mysqlib})
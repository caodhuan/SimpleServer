cmake_minimum_required(VERSION 2.8)

if(WIN32)
	file(GLOB hiredis_src ${CMAKE_CURRENT_SOURCE_DIR}/win/redis/deps/hiredis/async.c
		${CMAKE_CURRENT_SOURCE_DIR}/win/redis/deps/hiredis/hiredis.c
		${CMAKE_CURRENT_SOURCE_DIR}/win/redis/deps/hiredis/net.c
		${CMAKE_CURRENT_SOURCE_DIR}/win/redis/deps/hiredis/sds.c
		${CMAKE_CURRENT_SOURCE_DIR}/win/redis/deps/hiredis/async.h
		${CMAKE_CURRENT_SOURCE_DIR}/win/redis/deps/hiredis/fmacros.h
		${CMAKE_CURRENT_SOURCE_DIR}/win/redis/deps/hiredis/hiredis.h
		${CMAKE_CURRENT_SOURCE_DIR}/win/redis/deps/hiredis/net.h
		${CMAKE_CURRENT_SOURCE_DIR}/win/redis/deps/hiredis/sds.h
		${CMAKE_CURRENT_SOURCE_DIR}/win/redis/deps/hiredis/win32_hiredis.h
	)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/win/redis/deps/hiredis/)
	add_definitions(-DUNICODE -D_UNICODE -D_OFF_T_DEFINED -D_CRT_SECURE_NO_WARNINGS)
else()
	file(GLOB hiredis_src ${CMAKE_CURRENT_SOURCE_DIR}/linux/hiredis/net.*
		${CMAKE_CURRENT_SOURCE_DIR}/linux/hiredis/hiredis.*
		${CMAKE_CURRENT_SOURCE_DIR}/linux/hiredis/sds.*
		${CMAKE_CURRENT_SOURCE_DIR}/linux/hiredis/async.*
		${CMAKE_CURRENT_SOURCE_DIR}/linux/hiredis/read.*
	)
	add_definitions(-DUNICODE -D_UNICODE)
endif()

add_library(hiredis ${hiredis_src})

set_target_properties(hiredis PROPERTIES FOLDER 3rd)
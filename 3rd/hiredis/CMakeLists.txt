cmake_minimum_required(VERSION 2.8)

if(WIN32)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")	
	file(GLOB hiredis_src 
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/async.c
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/hiredis.c
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/net.c
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/sds.c
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/async.h
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/fmacros.h
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/hiredis.h
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/net.h
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/sds.h
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/win32_hiredis.h
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/msvs/Win32_Interop/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/msvs/Win32_Interop/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/msvs/Win32_Interop/*.c
		${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/msvs/deps/*

	)

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/win/hiredis/msvs/deps)

	add_definitions(-DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS )
	add_library(hiredis ${hiredis_src})


	target_compile_definitions(hiredis PUBLIC 
	getsockopt=redis_inter_getsockopt
	setsockopt=redis_inter_setsockopt
	htons=redis_inter_htons
	bind=redis_inter_bind
	getpeername=redis_inter_getpeername
	getsockname=redis_inter_getsockname
	listen=redis_inter_listen
	socket=redis_inter_socket
	htonl=redis_inter_htonl
	select=redis_inter_select
	)
else()
	file(GLOB hiredis_src 
		${CMAKE_CURRENT_SOURCE_DIR}/linux/hiredis/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/linux/hiredis/*.c
	)

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/linux/hiredis)

	add_definitions(-DUNICODE -D_UNICODE)

	add_library(hiredis ${hiredis_src})
endif()



set_target_properties(hiredis PROPERTIES FOLDER 3rd)

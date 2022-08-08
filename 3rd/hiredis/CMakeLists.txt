cmake_minimum_required(VERSION 3.2)

if(WIN32)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")	
	file(GLOB hiredis_src 
		${CMAKE_CURRENT_SOURCE_DIR}/windows/async.c
		${CMAKE_CURRENT_SOURCE_DIR}/windows/hiredis.c
		${CMAKE_CURRENT_SOURCE_DIR}/windows/net.c
		${CMAKE_CURRENT_SOURCE_DIR}/windows/sds.c
		${CMAKE_CURRENT_SOURCE_DIR}/windows/async.h
		${CMAKE_CURRENT_SOURCE_DIR}/windows/fmacros.h
		${CMAKE_CURRENT_SOURCE_DIR}/windows/hiredis.h
		${CMAKE_CURRENT_SOURCE_DIR}/windows/net.h
		${CMAKE_CURRENT_SOURCE_DIR}/windows/sds.h
		${CMAKE_CURRENT_SOURCE_DIR}/windows/win32_hiredis.h
		${CMAKE_CURRENT_SOURCE_DIR}/windows/msvs/Win32_Interop/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/windows/msvs/Win32_Interop/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/windows/msvs/Win32_Interop/*.c
		${CMAKE_CURRENT_SOURCE_DIR}/windows/msvs/deps/*

	)

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/windows)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/windows/msvs/deps)

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
		${CMAKE_CURRENT_SOURCE_DIR}/linux/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/linux/*.c
	)

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/linux)
	
	add_definitions(-DUNICODE -D_UNICODE)

	add_library(hiredis ${hiredis_src})
endif()



set_target_properties(hiredis PROPERTIES FOLDER 3rd)

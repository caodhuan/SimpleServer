cmake_minimum_required(VERSION 3.3)

# 项目生成调试信息
set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Od /Oy- /MTd")
set(CMAKE_C_FLAGS_DEBUG "/Zi /Od /Oy- /MTd")

# 可以使用文件夹
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_definitions(-DUNICODE -D_UNICODE)

if(WIN32)

	add_definitions(-DOS_WIN)

	file(GLOB leveldbsrc
		${CMAKE_CURRENT_SOURCE_DIR}/util/*.*
		${CMAKE_CURRENT_SOURCE_DIR}/table/*.*
		${CMAKE_CURRENT_SOURCE_DIR}/db/*.*
		${CMAKE_CURRENT_SOURCE_DIR}/include/leveldb/*.*
		${CMAKE_CURRENT_SOURCE_DIR}/helpers/memenv/*.*
		${CMAKE_CURRENT_SOURCE_DIR}/port/atomic_pointer.h
		${CMAKE_CURRENT_SOURCE_DIR}/port/port.h
		${CMAKE_CURRENT_SOURCE_DIR}/port/thread_annotations.h
		${CMAKE_CURRENT_SOURCE_DIR}/port/win/*.*
		${CMAKE_CURRENT_SOURCE_DIR}/snappy/*.*
		)
	INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/snappy)
	
	remove(leveldbsrc
		"${CMAKE_CURRENT_SOURCE_DIR}/util/env_posix.cc"
		"${CMAKE_CURRENT_SOURCE_DIR}/util/posix_logger.h"
		)

else()

add_definitions(-DLEVELDB_PLATFORM_POSIX)
	file(GLOB leveldbsrc
		${CMAKE_CURRENT_SOURCE_DIR}/util/*.*
		${CMAKE_CURRENT_SOURCE_DIR}/table/*.*
		${CMAKE_CURRENT_SOURCE_DIR}/db/*.*
		${CMAKE_CURRENT_SOURCE_DIR}/include/leveldb/*.*
		${CMAKE_CURRENT_SOURCE_DIR}/helpers/memenv/*.*
		${CMAKE_CURRENT_SOURCE_DIR}/port/*.*
		)

	remove(leveldbsrc
		"${CMAKE_CURRENT_SOURCE_DIR}/util/env_win32.h" 
		"${CMAKE_CURRENT_SOURCE_DIR}/util/env_win32.cc" 　
		"${CMAKE_CURRENT_SOURCE_DIR}/util/win_logger.cc" 
		"${CMAKE_CURRENT_SOURCE_DIR}/port/port_win.cc" 
		"${CMAKE_CURRENT_SOURCE_DIR}/util/port_win.h" 
		)
endif()


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

add_library(leveldb ${leveldbsrc})

set_target_properties(leveldb PROPERTIES FOLDER 3rd)
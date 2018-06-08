# 添加protobuf
file(GLOB pb ${CMAKE_CURRENT_SOURCE_DIR}/3rd/protobuf/cmake/*)
if(pb)
	message(STATUS "found protobuf")
	option(protobuf_BUILD_TESTS OFF)

	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rd/protobuf/cmake/)
	
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd/protobuf/src)

	set_target_properties(libprotobuf PROPERTIES FOLDER 3rd/protobuf)
	set_target_properties(libprotobuf-lite PROPERTIES FOLDER 3rd/protobuf)
	set_target_properties(libprotoc PROPERTIES FOLDER 3rd/protobuf)
	set_target_properties(protoc PROPERTIES FOLDER 3rd/protobuf)
	set_target_properties(js_embed PROPERTIES FOLDER 3rd/protobuf)

else()
	message("CANT find protobuf")
endif()


# libuv的cmake
add_subdirectory(3rd)

# hiredis
add_subdirectory(3rd/hiredis)

# leveldb
add_subdirectory(3rd/leveldb)

# lua 5.3.4
file(GLOB libluafilesrc )

foreach(files lapi.c lcode.c lctype.c ldebug.c ldo.c ldump.c lfunc.c lgc.c llex.c lmem.c lobject.c lopcodes.c lparser.c lstate.c lstring.c ltable.c ltm.c lundump.c lvm.c lzio.c lauxlib.c lbaselib.c lbitlib.c lcorolib.c ldblib.c liolib.c lmathlib.c loslib.c lstrlib.c ltablib.c lutf8lib.c loadlib.c linit.c)
	list(APPEND libluafilesrc "${CMAKE_CURRENT_SOURCE_DIR}/3rd/lua/src/${files}")
endforeach()

if(WIN32) 
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /Od /Oy- /MT")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od /Oy- /MTd")	
endif()


add_library(lua ${libluafilesrc})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd/lua/src/)

set_target_properties(lua PROPERTIES FOLDER 3rd)
#############################################################################
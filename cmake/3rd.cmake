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


# 只是protobuf的cmake
add_subdirectory(3rd)

# hiredis
add_subdirectory(3rd/hiredis)
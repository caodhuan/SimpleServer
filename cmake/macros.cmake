cmake_minimum_required(VERSION 3.2)

# 可以使用文件夹
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_definitions(-DUNICODE -D_UNICODE)

macro(group name)
	set(project_group ${name})
endmacro()

macro(endgroup)
	set(project_group "")
endmacro()

macro(addlib name path)
	file(GLOB_RECURSE files ${path}/*)
	add_library(${name} ${files})
	#set_target_properties(${name} PROPERTIES UNITY_BUILD ON)
	include_directories(${path})
	add2group(${name})
endmacro()

macro(addexec name path)
	file(GLOB_RECURSE files ${path}/*)
	add_executable(${name} ${files})
	set_target_properties(${name} PROPERTIES UNITY_BUILD ON)
	include_directories(${path})
	add2group(${name})

	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${PROJECT_BINARY_DIR}/)
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${PROJECT_BINARY_DIR}/Debug)
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${PROJECT_BINARY_DIR}/Release)
endmacro()


macro(add2group proj)
	if(NOT ${project_group} STREQUAL "")
		set_target_properties(${proj} PROPERTIES FOLDER ${project_group})
	endif()
endmacro()
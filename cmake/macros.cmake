
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
	file(GLOB files ${path}/*.[h|c]*)
	add_library(${name} ${files})
	include_directories(${path})
	add2group(${name})
endmacro()

macro(addexec name path)
	file(GLOB files ${path}/*)
	add_library(${name} ${files})
	include_directories(${path})
	add2group(${name})
endmacro()


macro(add2group proj)
	if(NOT ${project_group} STREQUAL "")
		set_target_properties(${proj} PROPERTIES FOLDER ${project_group})
	endif()
endmacro()
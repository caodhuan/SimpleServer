
# proto文件相关
# 先删除掉生成的文件，如果有的话
file(GLOB REMOVED
	${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/*.cc
	)
if(REMOVED)
	file(REMOVE ${REMOVED})
else()
	make_directory(${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/)
endif()

set(COMMONPROTOBUFHEADER "${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/commonprotobuf.h")

file(GLOB PROTO
	${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/*.proto
	)


# debug和release都尝试一下
# 这里需要先cmake一次,编译后，再cmake一次
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/3rd/protobuf/cmake/Debug/protoc.exe)
	set(protoexe  ${CMAKE_CURRENT_BINARY_DIR}/3rd/protobuf/cmake/Debug/protoc.exe)
elseif(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/3rd/protobuf/cmake/Release/protoc.exe)
	set(protoexe  ${CMAKE_CURRENT_BINARY_DIR}/3rd/protobuf/cmake/Debug/protoc.exe)
else()
	set(protoexe  ${CMAKE_CURRENT_BINARY_DIR}/3rd/protobuf/cmake/protoc)
endif()

execute_process(
	COMMAND ${protoexe} ${PROTO} -I=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/
)

file(GLOB GENERATEDSRC
	${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/*.cc
	)

file(GLOB GENERATEDHEAD
	${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/*.h
	)

source_group(GeneratedFiles FILES ${GENERATEDSRC} ${GENERATEDHEAD} )
source_group(protos FILES ${PROTO} )


if(EXISTS ${GENERATEDHEAD})
	file(WRITE ${COMMONPROTOBUFHEADER} "#pragma once\n")

	foreach(files ${GENERATEDHEAD})

		string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/" "" ONEHREAD ${files} )
		file(APPEND ${COMMONPROTOBUFHEADER} "#include \"${ONEHREAD}\"\n")
	endforeach()
endif()

group(base)
	addlib(common ${CMAKE_CURRENT_SOURCE_DIR}/libs/common)
	addlib(network ${CMAKE_CURRENT_SOURCE_DIR}/libs/network)
	addlib(db ${CMAKE_CURRENT_SOURCE_DIR}/libs/db)
	addlib(protos ${CMAKE_CURRENT_SOURCE_DIR}/libs/protos)
	addlib(server ${CMAKE_CURRENT_SOURCE_DIR}/libs/server)

	target_link_libraries(protos libprotobuf) 
	target_link_libraries(server network protos db common) 
	
endgroup()

# 增加custom build
add_custom_command(TARGET protos PRE_BUILD 
	COMMAND protoc ${PROTO} -I=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/ --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/
	)
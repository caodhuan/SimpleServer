
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
	${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/*.proto)

find_program (googleprotoc protoc)

if(googleprotoc) 
	execute_process(
	COMMAND ${googleprotoc} ${PROTO} -I=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/
	)

else()
	# debug和release都尝试一下
	# 这里需要先cmake一次,编译后，再cmake一次
	execute_process(
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/3rd/protobuf/cmake/Debug/protoc.exe ${PROTO} -I=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/
	)

	execute_process(
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/3rd/protobuf/cmake/Release/protoc.exe ${PROTO} -I=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/
	)
endif()



file(GLOB GENERATEDSRC
	${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/*.cc)

file(GLOB GENERATEDHEAD
	${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/*.h)

source_group(GeneratedFiles FILES ${GENERATEDSRC} ${GENERATEDHEAD} )
source_group(protos FILES ${PROTO} )

foreach(files ${GENERATEDHEAD})
	message(${files})

	string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/" "" ONEHREAD ${files} )
	string(APPEND COMMONINCLUDECONTENT "#include \"${ONEHREAD}\"\n")
endforeach()


if(COMMONINCLUDECONTENT)
	file(WRITE ${COMMONPROTOBUFHEADER} "#pragma once\n")
	file(APPEND ${COMMONPROTOBUFHEADER} ${COMMONINCLUDECONTENT})
endif()

group(base)
	addlib(common ${CMAKE_CURRENT_SOURCE_DIR}/libs/common)
	addlib(network ${CMAKE_CURRENT_SOURCE_DIR}/libs/network)
	addlib(db ${CMAKE_CURRENT_SOURCE_DIR}/libs/db)
	addlib(protos ${CMAKE_CURRENT_SOURCE_DIR}/libs/protos)
	addlib(server ${CMAKE_CURRENT_SOURCE_DIR}/libs/server)
endgroup()

# 增加custom build
	add_custom_command(TARGET protos PRE_BUILD 
		COMMAND protoc ${PROTO} -I=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/ --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/
		)
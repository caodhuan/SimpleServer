cmake_minimum_required(VERSION 3.2)


group(base)
	addlib(common ${CMAKE_CURRENT_SOURCE_DIR}/libs/common)
	addlib(network ${CMAKE_CURRENT_SOURCE_DIR}/libs/network)
	addlib(db ${CMAKE_CURRENT_SOURCE_DIR}/libs/db)
	addlib(protos ${CMAKE_CURRENT_SOURCE_DIR}/libs/protos)
	addlib(server ${CMAKE_CURRENT_SOURCE_DIR}/libs/server)
	addlib(resource ${CMAKE_CURRENT_SOURCE_DIR}/libs/resource)

	target_link_libraries(network common protos) 
	target_link_libraries(db hiredis) 
	target_link_libraries(protos ${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/libprotobuf.a)  # libprotobuf 在调用 cmake 时指定
	target_link_libraries(server resource network protos db common) 
endgroup()

#proto include 文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/include)

if(WIN32)
	set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/3rd/mysql/win)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /Od /Oy- /MD ") #mysqlclient只能是MD  ？
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od /Oy- /MTd")	
	set(mysqlclient_lib 
		optimized ${lib_path}/lib/mysqlclient.lib
		debug ${lib_path}/lib/libmysql.lib)

	file(COPY ${lib_path}/lib/libmysql.dll DESTINATION ${CMAKE_WORKING_DIRECTORY}/)
	file(COPY ${lib_path}/lib/libmysql.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug)

	target_link_libraries(db ws2_32.lib Psapi.lib IPHLPAPI.lib userenv.lib)
	
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd/hiredis/windows)
	include_directories(${lib_path}/include)
else()

	set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/3rd/mysql/linux)

	file(GLOB mysqlclient_lib ${lib_path}/lib/libmysqlclient.a)

	target_link_libraries(db pthread dl )

	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd/hiredis/linux)
	include_directories(${lib_path}/include)
endif()

target_link_libraries(db ${mysqlclient_lib})

# 增加custom build
# add_custom_command(TARGET protos PRE_BUILD 
# 	COMMAND protoc ${PROTO} -I=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/ --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/libs/protos/
# )

find_package(Boost 1.74.0 REQUIRED) 
if(Boost_FOUND)
	message("boost include and lib dirs: " ${Boost_INCLUDE_DIR} ", ")
	include_directories(${Boost_INCLUDE_DIR})
endif()

group(base)
	addlib(common ${CMAKE_CURRENT_SOURCE_DIR}/libs/common)
	addlib(network ${CMAKE_CURRENT_SOURCE_DIR}/libs/network)
	addlib(db ${CMAKE_CURRENT_SOURCE_DIR}/libs/db)
	addlib(protos ${CMAKE_CURRENT_SOURCE_DIR}/libs/protos)
	addlib(server ${CMAKE_CURRENT_SOURCE_DIR}/libs/server)
endgroup()
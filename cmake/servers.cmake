group(server)
	addexec(db_server ${CMAKE_CURRENT_SOURCE_DIR}/src/db)
	addexec(connector ${CMAKE_CURRENT_SOURCE_DIR}/src/connector)


	target_link_libraries(db_server server) 
	target_link_libraries(connector server)
endgroup()


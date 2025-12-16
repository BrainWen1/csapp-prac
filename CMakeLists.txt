cmake_minimum_required(VERSION 3.20)

project(csapp-prac LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
if(CMAKE_CONFIGURATION_TYPES)
	foreach(cfg ${CMAKE_CONFIGURATION_TYPES})
		string(TOUPPER "${cfg}" cfg_upper)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${cfg_upper} ${CMAKE_SOURCE_DIR}/bin)
	endforeach()
endif()

add_compile_definitions(
	_POSIX_C_SOURCE=200809L
)

add_compile_options(-Wno-format-overflow)

set(CSAPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CSAPP_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(MALLOC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/malloc)

find_package(Threads REQUIRED)

add_library(csapp STATIC
	${CSAPP_SRC_DIR}/csapp.c
)
target_include_directories(csapp
	PUBLIC
		${CSAPP_INCLUDE_DIR}
)
target_link_libraries(csapp
	PUBLIC
		Threads::Threads
		m
)

add_library(csapp_malloc STATIC
	${MALLOC_DIR}/mm.c
	${MALLOC_DIR}/memlib.c
)
target_include_directories(csapp_malloc
	PUBLIC
		${CSAPP_INCLUDE_DIR}
)

option(BUILD_NETP_EXAMPLES "Build the network programming example programs" ON)

if(BUILD_NETP_EXAMPLES)
	# add_executable(hostinfo netp/hostinfo.c netp/netpfragments.c)
	# target_link_libraries(hostinfo PRIVATE csapp)

	# add_executable(echoclient netp/echoclient.c)
	# target_link_libraries(echoclient PRIVATE csapp)

	# add_executable(echoserveri netp/echoserveri.c)
	# target_link_libraries(echoserveri PRIVATE csapp)

	# add_executable(tiny netp/tiny/tiny.c)
	# target_link_libraries(tiny PRIVATE csapp)

	# add_executable(cgi_adder netp/tiny/cgi-bin/adder.c)
	# target_include_directories(cgi_adder PRIVATE ${CSAPP_INCLUDE_DIR})
	# set_target_properties(cgi_adder PROPERTIES
	# 	OUTPUT_NAME adder
	# 	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tiny-cgi
	# )
	# add_custom_command(TARGET cgi_adder POST_BUILD
	# 	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/netp/tiny/cgi-bin
	# 	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:cgi_adder> ${CMAKE_SOURCE_DIR}/netp/tiny/cgi-bin/adder
	# )

	# add_executable(echoserverp ./conc/echoserverp.c)
	# target_link_libraries(echoserverp PRIVATE csapp)

	# add_executable(select ./conc/select.c)
	# target_link_libraries(select PRIVATE csapp)

	# add_executable(echoservers ./conc/echoservers.c)
	# target_link_libraries(echoservers PRIVATE csapp)

	# add_executable(hello ./conc/hello.c)
	# target_link_libraries(hello PRIVATE csapp)

	add_executable(shellex ./ecf/shellex.c)
	target_link_libraries(shellex PRIVATE csapp)
endif()

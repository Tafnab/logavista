
include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_tiger_sources
	tigerConfigurationWidget.cpp
	tigerConfiguration.cpp
	tigerLogMode.cpp
	tigerFactory.cpp
)

add_library(ksystemlog_tiger STATIC ${ksystemlog_tiger_sources})

add_dependencies(
	ksystemlog_tiger
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_tiger
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
)

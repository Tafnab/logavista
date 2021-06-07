
include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_powerlogs_sources
	powerlogsConfigurationWidget.cpp
	powerlogsConfiguration.cpp
	powerlogsLogMode.cpp
	powerlogsFactory.cpp
)

add_library(ksystemlog_powerlogs STATIC ${ksystemlog_powerlogs_sources})

add_dependencies(
	ksystemlog_powerlogs
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_powerlogs
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
)

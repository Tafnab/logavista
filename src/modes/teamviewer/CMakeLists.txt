
include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_teamviewer_sources
	teamviewerConfigurationWidget.cpp
	teamviewerConfiguration.cpp
	teamviewerLogMode.cpp
	teamviewerFactory.cpp
)

add_library(ksystemlog_teamviewer STATIC ${ksystemlog_teamviewer_sources})

add_dependencies(
	ksystemlog_teamviewer
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_teamviewer
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
)

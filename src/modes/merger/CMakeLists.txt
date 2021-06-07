
include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_merger_sources
	mergerConfigurationWidget.cpp
	mergerConfiguration.cpp
	mergerLogMode.cpp
	mergerFactory.cpp
	mergerAnalyzer.cpp
)

add_library(ksystemlog_merger STATIC ${ksystemlog_merger_sources})

add_dependencies(
	ksystemlog_merger
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_merger
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
	
	
        KF5::KIOWidgets
	
)

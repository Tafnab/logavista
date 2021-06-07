
include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_rkhunter_sources
	rkhunterConfigurationWidget.cpp
	rkhunterConfiguration.cpp
	rkhunterLogMode.cpp
	rkhunterFactory.cpp
)

add_library(ksystemlog_rkhunter STATIC ${ksystemlog_rkhunter_sources})

add_dependencies(
	ksystemlog_rkhunter
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_rkhunter
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
)


include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_firewall_sources
	firewallConfigurationWidget.cpp
	firewallConfiguration.cpp
	firewallLogMode.cpp
	firewallFactory.cpp
)

add_library(ksystemlog_firewall STATIC ${ksystemlog_firewall_sources})

add_dependencies(
	ksystemlog_firewall
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_firewall
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
)

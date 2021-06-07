
include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_mx_boot_repair_sources
	mx_boot_repairConfigurationWidget.cpp
	mx_boot_repairConfiguration.cpp
	mx_boot_repairLogMode.cpp
	mx_boot_repairFactory.cpp
)

add_library(ksystemlog_mx_boot_repair STATIC ${ksystemlog_mx_boot_repair_sources})

add_dependencies(
	ksystemlog_mx_boot_repair
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_mx_boot_repair
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
)

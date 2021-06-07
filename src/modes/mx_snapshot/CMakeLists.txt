
include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_mx_snapshot_sources
	mx_snapshotConfigurationWidget.cpp
	mx_snapshotConfiguration.cpp
	mx_snapshotLogMode.cpp
	mx_snapshotFactory.cpp
)

add_library(ksystemlog_mx_snapshot STATIC ${ksystemlog_mx_snapshot_sources})

add_dependencies(
	ksystemlog_mx_snapshot
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_mx_snapshot
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
)

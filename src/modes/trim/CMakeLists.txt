
include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_trim_sources
	trimConfigurationWidget.cpp
	trimConfiguration.cpp
	trimLogMode.cpp
	trimFactory.cpp
)

add_library(ksystemlog_trim STATIC ${ksystemlog_trim_sources})

add_dependencies(
	ksystemlog_trim
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_trim
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
)

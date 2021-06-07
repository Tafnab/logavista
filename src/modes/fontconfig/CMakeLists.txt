
include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_fontconfig_sources
	fontconfigConfigurationWidget.cpp
	fontconfigConfiguration.cpp
	fontconfigLogMode.cpp
	fontconfigFactory.cpp
)

add_library(ksystemlog_fontconfig STATIC ${ksystemlog_fontconfig_sources})

add_dependencies(
	ksystemlog_fontconfig
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_fontconfig
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
)

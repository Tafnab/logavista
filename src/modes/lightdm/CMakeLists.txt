
include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_lightdm_sources
	lightdmConfigurationWidget.cpp
	lightdmConfiguration.cpp
	lightdmLogMode.cpp
	lightdmFactory.cpp
)

add_library(ksystemlog_lightdm STATIC ${ksystemlog_lightdm_sources})

add_dependencies(
	ksystemlog_lightdm
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_lightdm
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
)

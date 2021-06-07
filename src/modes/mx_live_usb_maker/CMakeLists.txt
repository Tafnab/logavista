
include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_mx_live_usb_maker_sources
	mx_live_usb_makerConfigurationWidget.cpp
	mx_live_usb_makerConfiguration.cpp
	mx_live_usb_makerLogMode.cpp
	mx_live_usb_makerFactory.cpp
)

add_library(ksystemlog_mx_live_usb_maker STATIC ${ksystemlog_mx_live_usb_maker_sources})

add_dependencies(
	ksystemlog_mx_live_usb_maker
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_mx_live_usb_maker
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
)

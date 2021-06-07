
include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_formatusb_sources
	formatusbConfigurationWidget.cpp
	formatusbConfiguration.cpp
	formatusbLogMode.cpp
	formatusbFactory.cpp
	formatusbAnalyzer.cpp
)

add_library(ksystemlog_formatusb STATIC ${ksystemlog_formatusb_sources})

add_dependencies(
	ksystemlog_formatusb
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_formatusb
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
	
	
        KF5::KIOWidgets
	
)

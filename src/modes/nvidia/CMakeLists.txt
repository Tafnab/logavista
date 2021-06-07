
include_directories( 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../base
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
	${CMAKE_CURRENT_SOURCE_DIR}/../../config 
        ${CMAKE_CURRENT_BINARY_DIR}/../base
        ${CMAKE_CURRENT_BINARY_DIR}/../../config
)

set(ksystemlog_nvidia_sources
	nvidiaConfigurationWidget.cpp
	nvidiaConfiguration.cpp
	nvidiaLogMode.cpp
	nvidiaFactory.cpp
)

add_library(ksystemlog_nvidia STATIC ${ksystemlog_nvidia_sources})

add_dependencies(
	ksystemlog_nvidia
	ksystemlog_base_mode 
	ksystemlog_lib
)

target_link_libraries(
	ksystemlog_nvidia
	
	ksystemlog_lib
	ksystemlog_base_mode 
	ksystemlog_config
)

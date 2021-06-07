project(logavista)

# KDE Application Version, managed by release script
set (KDE_APPLICATIONS_VERSION_MAJOR "00")
set (KDE_APPLICATIONS_VERSION_MINOR "09")
set (KDE_APPLICATIONS_VERSION_MICRO "0")
set (KDE_APPLICATIONS_VERSION "${KDE_APPLICATIONS_VERSION_MAJOR}.${KDE_APPLICATIONS_VERSION_MINOR}.${KDE_APPLICATIONS_VERSION_MICRO}")

cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)
set (QT_MIN_VERSION "5.2.0")
set (KF5_MIN_VERSION "5.0.0")

find_package (ECM 1.7.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_definitions(-DTRANSLATION_DOMAIN="ksystemlog")

include(ECMSetupVersion)
include(KDEInstallDirs)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(FeatureSummary)
#include(CPack)

ecm_setup_version(${KDE_APPLICATIONS_VERSION} VARIABLE_PREFIX KSYSTEMLOG
                  VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/src/ksystemlog_version.h")

find_package (Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Concurrent
    Core
    Network
    Widgets
    Test
    PrintSupport
)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    XmlGui
    CoreAddons
    WidgetsAddons
    ItemViews
    IconThemes
    KIO
    Config
    Archive
    DocTools
    I18n
    Completion
    TextWidgets
)



include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckSymbolExists)
include(CheckFunctionExists)
include(CheckLibraryExists)
include(CheckTypeSize)

add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS -DQT_NO_URL_CAST_FROM_STRING)
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Help Eclipse to parse errors more efficiently
if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
endif(CMAKE_COMPILER_IS_GNUCC)
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
endif(CMAKE_COMPILER_IS_GNUCXX)


add_custom_target(
    pkg
    COMMAND ./build-package.sh
)



##
# To specify a different install prefix, use :
# cmake -D CMAKE_INSTALL_PREFIX=build .
#
# To help Eclipse discover include paths, use :
# cmake -D CMAKE_VERBOSE_MAKEFILE=true .
##


set(_fmt TGZ)
if(WIN32)
          set(_fmt ZIP)
  endif()
  set(CPACK_GENERATOR ${_fmt})
  set(CPACK_SOURCE_GENERATOR ${_fmt})
  set(CPACK_PACKAGE_VENDOR "J.D. Nicholson")
  set(CPACK_PACKAGE_CONTACT "Your Name")
  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
  set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
  set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/package")
  set(CPACK_PACKAGE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  string(TOLOWER ${CMAKE_SYSTEM_NAME} _sys)
  string(TOLOWER ${PROJECT_NAME} _project_lower)
  set(CPACK_PACKAGE_FILE_NAME "${_project_lower}-${_sys}")
  set(CPACK_SOURCE_PACKAGE_FILE_NAME "${_project_lower}-${PROJECT_VERSION}")

  # not .gitignore as its regex syntax is distinct
  set(CPACK_SOURCE_IGNORE_FILES "/build/;/extrafiles/;/temp/;/lib/;/tests/;*.kdev4;/doc/")

  install(FILES ${CPACK_RESOURCE_FILE_README} ${CPACK_RESOURCE_FILE_LICENSE}
            DESTINATION share/docs/${PROJECT_NAME})
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/icons/"  DESTINATION /usr/local/share/icons/logavista 
        PATTERN "*" )

  include(CPack)

########### Subfolders ##########

add_subdirectory(src)
add_subdirectory(src/lib)
add_subdirectory(src/config)

add_subdirectory(src/modes/base)
add_subdirectory(src/modes/open)

add_subdirectory(src/modes/system)
add_subdirectory(src/modes/kernel)
add_subdirectory(src/modes/xorg)
add_subdirectory(src/modes/cron)
add_subdirectory(src/modes/authentication)
add_subdirectory(src/modes/daemon)
add_subdirectory(src/modes/acpid)
add_subdirectory(src/modes/xsession)
add_subdirectory(src/modes/apache)
add_subdirectory(src/modes/postfix)
add_subdirectory(src/modes/samba)
add_subdirectory(src/modes/cups)
add_subdirectory(src/modes/alternatives)
add_subdirectory(src/modes/powerlogs)
add_subdirectory(src/modes/nvidia)
add_subdirectory(src/modes/fontconfig)
add_subdirectory(src/modes/formatusb)
add_subdirectory(src/modes/firewall)
add_subdirectory(src/modes/lightdm)
add_subdirectory(src/modes/trim)
add_subdirectory(src/modes/rkhunter)
add_subdirectory(src/modes/tiger)
add_subdirectory(src/modes/mx_boot_repair)
add_subdirectory(src/modes/mx_live_usb_maker)
add_subdirectory(src/modes/mx_snapshot)
add_subdirectory(src/modes/teamviewer)
add_subdirectory(src/modes/merger)



find_package(KF5I18n CONFIG REQUIRED)
ki18n_install(po)
kdoctools_install(po)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

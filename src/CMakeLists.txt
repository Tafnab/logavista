
########### Build ###############

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/config
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_BINARY_DIR}/config
    ${CMAKE_CURRENT_BINARY_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}

    ${CMAKE_CURRENT_SOURCE_DIR}/modes/open

    ${CMAKE_CURRENT_SOURCE_DIR}/modes/system
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/kernel
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/daemon
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/xorg
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/cron
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/acpid
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/xsession
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/apache
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/cups
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/samba
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/authentication
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/postfix
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/alternatives
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/powerlogs
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/nvidia
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/fontconfig
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/formatusb
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/lightdm
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/trim
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/rkhunter
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/tiger
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/mx_boot_repair
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/mx_live_usb_maker
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/mx_snapshot
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/teamviewer
    ${CMAKE_CURRENT_SOURCE_DIR}/modes/merger
)

set(ksystemlog_sources
    main.cpp
    mainWindow.cpp
    logModePluginsLoader.cpp
    loggerDialog.cpp
    detailDialog.cpp
    generalConfigurationWidget.cpp
    configurationDialog.cpp
    tabLogViewsWidget.cpp
    tabLogManager.cpp
    statusBar.cpp
)

ki18n_wrap_ui(ksystemlog_sources
    detailDialogBase.ui
    loggerDialogBase.ui
    generalConfigurationWidgetBase.ui
)

add_executable(logavista ${ksystemlog_sources})

target_link_libraries(logavista
    ksystemlog_lib
    ksystemlog_config
    ksystemlog_open
    ksystemlog_system
    ksystemlog_kernel
    ksystemlog_xorg
    ksystemlog_cron
    ksystemlog_apache
    ksystemlog_authentication
    ksystemlog_daemon
    ksystemlog_acpid
    ksystemlog_xsession
    ksystemlog_postfix
    ksystemlog_cups
    ksystemlog_samba
    ksystemlog_alternatives
    ksystemlog_powerlogs
    ksystemlog_nvidia
    ksystemlog_firewall
    ksystemlog_fontconfig
    ksystemlog_formatusb
    ksystemlog_lightdm
    ksystemlog_trim
    ksystemlog_rkhunter
    ksystemlog_tiger
    ksystemlog_mx_boot_repair
    ksystemlog_mx_live_usb_maker
    ksystemlog_mx_snapshot
    ksystemlog_teamviewer
    ksystemlog_merger

    KF5::Archive
    KF5::TextWidgets
)


########### Installation ###############

install(TARGETS logavista ${INSTALL_TARGETS_DEFAULT_ARGS} )

install(PROGRAMS logavista.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} RENAME logavista)
install(FILES logavistaui.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/logavista)



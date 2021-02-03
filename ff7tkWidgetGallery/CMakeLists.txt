project(ff7tkWidgetGallery VERSION 0.1.1 DESCRIPTION "Demo App for ff7tk with widgets")

set(CMAKE_AUTOUIC ON)
set(WIDGETS ON CACHE BOOL BOOL FORCE)
set(FORMATS ON CACHE BOOL BOOL FORCE)

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
        Widgets
        Quick
    )

set ( ff7tkWidgetGallery_SRCS
        main.cpp
        mainwindow.cpp
    )

if (UNIX AND NOT APPLE)
    add_executable ( ff7tkWidgetGallery ${ff7tkWidgetGallery_SRCS})
    install(TARGETS ff7tkWidgetGallery RUNTIME DESTINATION bin)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.desktop" DESTINATION share/applications/)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.png" DESTINATION share/pixmaps)

elseif(APPLE)
    set(CMAKE_INSTALL_REMOVE_ENVIRONMENT_RPATH ON)
    set(APPICON ${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.icns)
    set(MACOSX_BUNDLE_DISPLAY_NAME "ff7tkWidgetGallery")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.ff7tk.WidgetGallery")
    set(MACOSX_BUNDLE_BUNDLE_NAME "ff7tkWidgetGallery")
    set(MACOSX_BUNDLE_DISPLAY_NAME "ff7tkWidgetGallery")
    set(MACOSX_BUNDLE_INFO_STRING "ff7tk - WidgetGallery")
    set(MACOSX_BUNDLE_COPYRIGHT "2012-2020 ff7tk Authors")
    set(MAXOSX_BUNDLE_ICON_FILE ff7tkWidgetGallery.icns)
    set_source_files_properties(${APPICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    add_executable(ff7tkWidgetGallery MACOSX_BUNDLE ${ff7tkWidgetGallery_SRCS} ${APPICON})
    install(TARGETS ff7tkWidgetGallery BUNDLE DESTINATION bin)

elseif(WIN32)
    add_executable ( ff7tkWidgetGallery WIN32 ${ff7tkWidgetGallery_SRCS} ff7tkWidgetGallery.rc)
    install(TARGETS ff7tkWidgetGallery RUNTIME DESTINATION bin)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.desktop" DESTINATION share/applications/)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.png" DESTINATION share/pixmaps)
endif()

target_include_directories (ff7tkWidgetGallery PRIVATE ${CMAKE_BINARY_DIR}/src/data ${CMAKE_BINARY_DIR}/src/widgets ${CMAKE_BINARY_DIR}/src/formats)

target_link_libraries ( ff7tkWidgetGallery
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Quick
        ff7tk::ff7tk
        ff7tk::ff7tkUtils
        ff7tk::ff7tkFormats
        ff7tk::ff7tkWidgets
    )

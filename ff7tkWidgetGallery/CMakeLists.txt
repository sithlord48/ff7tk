project(ff7tkWidgetGallery VERSION 0.1.1 DESCRIPTION "Demo App for ff7tk with widgets")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

set(WIDGETS ON CACHE BOOL BOOL FORCE)
set(FORMATS ON CACHE BOOL BOOL FORCE)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED NO_MODULE COMPONENTS
        Widgets
        Quick
)

if(APPLE)
    set(PLATFORM_EX_SRC ${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.icns)
    set_source_files_properties(${PLATFORM_EX_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
elseif(WIN32)
    set(PLATFORM_EX_SRC ff7tkWidgetGallery.rc)
endif()

add_executable(ff7tkWidgetGallery WIN32 MACOSX_BUNDLE
        main.cpp
        mainwindow.cpp
        ${PLATFORM_EX_SRC}
    )

add_dependencies(ff7tkWidgetGallery ff7tk ff7tkFormats ff7tkUtils ff7tkWidgets)

target_include_directories(ff7tkWidgetGallery PRIVATE
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src/data>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src/widgets>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src/formats>
)

target_link_libraries ( ff7tkWidgetGallery PRIVATE
        Qt::Widgets
        Qt::Quick
        ff7tk::ff7tk
        ff7tk::ff7tkUtils
        ff7tk::ff7tkFormats
        ff7tk::ff7tkWidgets
    )

if(APPLE)
    set_target_properties(ff7tkWidgetGallery PROPERTIES
        INSTALL_RPATH @loader_path
        BUILD_WITH_INSTALL_RPATH TRUE
        MACOSX_BUNDLE_DISPLAY_NAME "ff7tkWidgetGallery"
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.ff7tk.WidgetGallery"
        MACOSX_BUNDLE_BUNDLE_NAME "ff7tkWidgetGallery"
        MACOSX_BUNDLE_DISPLAY_NAME "ff7tkWidgetGallery"
        MACOSX_BUNDLE_INFO_STRING "ff7tk - WidgetGallery"
        MACOSX_BUNDLE_COPYRIGHT "2012-2020 ff7tk Authors"
        MAXOSX_BUNDLE_ICON_FILE ff7tkWidgetGallery.icns
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    )
elseif(UNIX AND NOT APPLE)
    set_target_properties(ff7tkWidgetGallery PROPERTIES
        INSTALL_RPATH "\$ORIGIN/../lib"
    )
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.desktop" DESTINATION share/applications/)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.png" DESTINATION share/pixmaps)
endif()

install(TARGETS ff7tkWidgetGallery
    BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

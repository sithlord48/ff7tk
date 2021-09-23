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

find_library(ff7tk ${CMAKE_BINARY_DIR}/src/data)
find_library(ff7tkFormats ${CMAKE_BINARY_DIR}/src/formats)
find_library(ff7tkUtils ${CMAKE_BINARY_DIR}/src/utils)
find_library(ff7tkWidgets ${CMAKE_BINARY_DIR}/src/widgets)

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

if(${BUILD_FRAMEWORKS})
    target_include_directories(ff7tkWidgetGallery PRIVATE
        $<BUILD_INTERFACE:$<TARGET_BUNDLE_CONTENT_DIR:ff7tk>/Headers>
        $<BUILD_INTERFACE:$<TARGET_BUNDLE_CONTENT_DIR:ff7tkFormats>/Headers>
        $<BUILD_INTERFACE:$<TARGET_BUNDLE_CONTENT_DIR:ff7tkUtils>/Headers>
        $<BUILD_INTERFACE:$<TARGET_BUNDLE_CONTENT_DIR:ff7tkWidgets>/Headers>
    )
else()
    target_include_directories(ff7tkWidgetGallery PRIVATE
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src/data>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src/formats>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src/utils>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src/widgets>
    )
endif()
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
        MACOSX_BUNDLE_DISPLAY_NAME "ff7tkWidgetGallery"
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.ff7tk.WidgetGallery"
        MACOSX_BUNDLE_BUNDLE_NAME "ff7tkWidgetGallery"
        MACOSX_BUNDLE_DISPLAY_NAME "ff7tkWidgetGallery"
        MACOSX_BUNDLE_INFO_STRING "ff7tk - WidgetGallery"
        MACOSX_BUNDLE_COPYRIGHT "2012-2020 ff7tk Authors"
        MAXOSX_BUNDLE_ICON_FILE ff7tkWidgetGallery.icns
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    )
    get_target_property(_qmake_executable Qt${QT_VERSION_MAJOR}::qmake IMPORTED_LOCATION)
    find_program(MACDEPLOYQT macdeployqt HINTS "${_qt_bin_dir}")
    add_custom_command(TARGET ff7tkWidgetGallery POST_BUILD
        COMMAND ${MACDEPLOYQT} ${PROJECT_NAME}.app
    )

elseif(UNIX AND NOT APPLE)
    set_target_properties(ff7tkWidgetGallery PROPERTIES
        INSTALL_RPATH "\$ORIGIN/../lib"
    )
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.desktop" DESTINATION share/applications/ COMPONENT ff7tkWidgetGallery_RUNTIME)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.png" DESTINATION share/pixmaps COMPONENT ff7tkWidgetGallery_RUNTIME)
endif()

install(TARGETS ff7tkWidgetGallery
    BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT ff7tkWidgetGallery_RUNTIME
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT ff7tkWidgetGallery_RUNTIME
)


project(ff7tkQmlGallery VERSION 0.1.1 LANGUAGES CXX DESCRIPTION "Demo App for ff7tk using QML")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Quick QuickControls2 QmlImportScanner)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED NO_MODULE COMPONENTS
        Quick
        QuickControls2
)

if(APPLE)
    set(PLATFORM_EX_SRC ${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.icns)
    set_source_files_properties(${PLATFORM_EX_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
elseif(WIN32)
    set(PLATFORM_EX_SRC ff7tkQmlGallery.rc)
endif()

add_executable(ff7tkQmlGallery WIN32 MACOSX_BUNDLE
        main.cpp
        qml.qrc
        ${PLATFORM_EX_SRC}
)

add_dependencies(ff7tkQmlGallery ff7tk)

target_include_directories(ff7tkQmlGallery
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src/data>
)

target_link_libraries ( ff7tkQmlGallery PUBLIC
        Qt::Quick
        Qt::QuickControls2
        ff7tk::ff7tk
)

if(APPLE)
    set_target_properties(ff7tkQmlGallery PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.ff7tk.QmlGallery"
        MACOSX_BUNDLE_DISPLAY_NAME "ff7tkQmlGallery"
        MACOSX_BUNDLE_BUNDLE_NAME "ff7tkQmlGallery"
        MACOSX_BUNDLE_DISPLAY_NAME "ff7tkQmlGallery"
        MACOSX_BUNDLE_INFO_STRING "ff7tk - QmlGallery"
        MACOSX_BUNDLE_COPYRIGHT "2012-2020 ff7tk Authors"
        MAXOSX_BUNDLE_ICON_FILE ff7tkQmlGallery.icns
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    )
    get_target_property(_qmake_executable Qt${QT_VERSION_MAJOR}::qmake IMPORTED_LOCATION)
    find_program(MACDEPLOYQT macdeployqt HINTS "${_qt_bin_dir}")
    add_custom_command(TARGET ff7tkQmlGallery POST_BUILD
        COMMAND ${MACDEPLOYQT} ${PROJECT_NAME}.app -qmldir=${CMAKE_SOURCE_DIR}/ff7tkQmlGallery
    )

elseif(UNIX AND NOT APPLE)
    set_target_properties(ff7tkQmlGallery PROPERTIES
        INSTALL_RPATH "\$ORIGIN/../lib"
    )
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.desktop" DESTINATION share/applications/ COMPONENT ff7tkQmlGallery_RUNTIME)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.png" DESTINATION share/pixmaps COMPONENT ff7tkQmlGallery_RUNTIME)
endif()

install(TARGETS ff7tkQmlGallery
    BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
     COMPONENT ff7tkQmlGallery_RUNTIME
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
     COMPONENT ff7tkQmlGallery_RUNTIME
)

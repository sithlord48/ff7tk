project(ff7tkQmlGallery VERSION 0.1.1 LANGUAGES CXX DESCRIPTION "Demo App for ff7tk using QML")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt${QT_DEFAULT_MAJOR_VERSION} REQUIRED NO_MODULE COMPONENTS
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
    add_custom_command(TARGET ff7tkQmlGallery POST_BUILD
        COMMAND ${PLATFORMDEPLOYQT} ${PROJECT_NAME}.app -qmldir=${CMAKE_CURRENT_SOURCE_DIR}
    )
elseif(UNIX AND NOT APPLE)
    set_target_properties(ff7tkQmlGallery PROPERTIES
        INSTALL_RPATH ${INSTALL_RPATH_STRING}
    )
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.desktop" DESTINATION share/applications/ COMPONENT ff7tkQmlGallery)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.png" DESTINATION share/pixmaps COMPONENT ff7tkQmlGallery)
endif()

install(TARGETS ff7tkQmlGallery
    COMPONENT ff7tkQmlGallery
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set_property(GLOBAL APPEND PROPERTY ff7tk_targets ff7tkQmlGallery)
list(APPEND CPACK_PACKAGE_EXECUTABLES "ff7tkQmlGallery;ff7tkQmlGallery")

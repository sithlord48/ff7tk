project(ff7tkQmlGallery VERSION 0.1.1 DESCRIPTION "Demo App for ff7tk using QML")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Quick QuickControls2 QmlImportScanner)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED NO_MODULE COMPONENTS
        Quick
        QuickControls2
)
find_library(FF7TK_LIB ff7tk)

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

target_include_directories(ff7tkQmlGallery PRIVATE
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src/data>
)

target_link_libraries ( ff7tkQmlGallery PRIVATE
        Qt::Quick
        Qt::QuickControls2
        ff7tk::ff7tk
)

if(APPLE)
    set_target_properties(ff7tkQmlGallery PROPERTIES
        INSTALL_RPATH @loader_path
        BUILD_WITH_INSTALL_RPATH TRUE
        MACOSX_BUNDLE_DISPLAY_NAME "ff7tkQmlGallery"
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.ff7tk.QmlGallery"
        MACOSX_BUNDLE_BUNDLE_NAME "ff7tkQmlGallery"
        MACOSX_BUNDLE_DISPLAY_NAME "ff7tkQmlGallery"
        MACOSX_BUNDLE_INFO_STRING "ff7tk - QmlGallery"
        MACOSX_BUNDLE_COPYRIGHT "2012-2020 ff7tk Authors"
        MAXOSX_BUNDLE_ICON_FILE ff7tkQmlGallery.icns
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    )
add_custom_command(
     TARGET ff7tkQmlGallery POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/src/data/libff7tk.${CMAKE_PROJECT_VERSION}.dylib ff7tkQmlGallery.app/Contents/MacOS/
     COMMAND ${CMAKE_COMMAND} -E rename ff7tkQmlGallery.app/Contents/MacOS/libff7tk.${CMAKE_PROJECT_VERSION}.dylib ff7tkQmlGallery.app/Contents/MacOS/libff7tk.${CMAKE_PROJECT_VERSION_MAJOR}.dylib
 )
    #install(FILES ${CMAKE_BINARY_DIR}/src/data/libff7tk.${CMAKE_PROJECT_VERSION}.dylib DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ff7tkQmlGallery.app/Contents/MacOS/ RENAME libff7tk.0.dylib)
elseif(UNIX AND NOT APPLE)
    set_target_properties(ff7tkQmlGallery PROPERTIES
        INSTALL_RPATH "\$ORIGIN/../lib"
    )
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.desktop" DESTINATION share/applications/)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.png" DESTINATION share/pixmaps)
endif()

install(TARGETS ff7tkQmlGallery
    BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

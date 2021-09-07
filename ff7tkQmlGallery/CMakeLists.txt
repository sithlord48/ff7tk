project(ff7tkQmlGallery)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(../src)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Quick QuickControls2 QmlImportScanner)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED NO_MODULE COMPONENTS
        Quick
        QuickControls2
        QmlImportScanner
    )

set ( ff7tkQmlGallery_SRCS
        main.cpp
        qml.qrc
    )

if (UNIX AND NOT APPLE)
    add_executable ( ff7tkQmlGallery ${ff7tkQmlGallery_SRCS})
    install(TARGETS ff7tkQmlGallery RUNTIME DESTINATION bin)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.desktop" DESTINATION share/applications/)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.png" DESTINATION share/pixmaps)

elseif(APPLE)
    set(CMAKE_INSTALL_REMOVE_ENVIRONMENT_RPATH ON)
    set(APPICON ${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.icns)
    set(MACOSX_BUNDLE_DISPLAY_NAME "ff7tkQmlGallery")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.ff7tk.WidgetGallery")
    set(MACOSX_BUNDLE_BUNDLE_NAME "ff7tkQmlGallery")
    set(MACOSX_BUNDLE_DISPLAY_NAME "ff7tkQmlGallery")
    set(MACOSX_BUNDLE_INFO_STRING "ff7tk - WidgetGallery")
    set(MACOSX_BUNDLE_COPYRIGHT "2012-2020 ff7tk Authors")
    set(MAXOSX_BUNDLE_ICON_FILE ff7tkQmlGallery.icns)
    set_source_files_properties(${APPICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    add_executable(ff7tkQmlGallery MACOSX_BUNDLE ${ff7tkQmlGallery_SRCS} ${APPICON})
    install(TARGETS ff7tkQmlGallery BUNDLE DESTINATION bin)

elseif(WIN32)
    add_executable ( ff7tkQmlGallery WIN32 ${ff7tkQmlGallery_SRCS} ff7tkQmlGallery.rc)
    install(TARGETS ff7tkQmlGallery RUNTIME DESTINATION bin)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.desktop" DESTINATION share/applications/)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.png" DESTINATION share/pixmaps)
endif()

target_include_directories (ff7tkQmlGallery PRIVATE ${CMAKE_BINARY_DIR}/src/data)

target_link_libraries ( ff7tkQmlGallery
        Qt::Core
        Qt::Gui
        Qt::Quick
        Qt::QuickControls2
        ff7tk::ff7tk
    )

qt_import_qml_plugins(ff7tkQmlGallery)

project(ff7tkWidgetGallery VERSION 0.1.1 DESCRIPTION "Demo App for ff7tk with widgets")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

set(WIDGETS ON CACHE BOOL BOOL FORCE)
set(FORMATS ON CACHE BOOL BOOL FORCE)

find_package(Qt${QT_DEFAULT_MAJOR_VERSION} REQUIRED NO_MODULE COMPONENTS
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
    add_custom_command(TARGET ff7tkWidgetGallery POST_BUILD
        COMMAND ${PLATFORMDEPLOYQT} ${PROJECT_NAME}.app
    )

elseif(UNIX AND NOT APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INSTALL_RPATH ${INSTALL_RPATH_STRING}
    )
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.desktop" DESTINATION share/applications/ COMPONENT ff7tkWidgetGallery)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.png" DESTINATION share/pixmaps COMPONENT ff7tkWidgetGallery)
endif()

install(TARGETS ff7tkWidgetGallery
    COMPONENT ff7tkWidgetGallery
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set_property(GLOBAL APPEND PROPERTY ff7tk_targets ff7tkWidgetGallery)
list(APPEND CPACK_PACKAGE_EXECUTABLES ff7tkWidgetGallery "ff7tk Widget Gallery")

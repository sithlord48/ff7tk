set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

#ff7tk Demo Applications
option(WIDGET_GALLERY "Build the widget based gallery" ON)
option(QML_GALLERY "Build the qml based gallery" ON)

#This Macro Creates a ff7tk demo from a project
#Then Sets all install and pacakge info
##REQUIREMENTS
# The INSTALL_RPATH_STRING has been set (main CMakeLists.txt)
# Caller is a project with NAME VERSION AND DESCRIPTION set
# DEMO_NAME_SRC - Source for the demo
# DEMO_NAME_DEPENDS - ff7tk items the demo depends on
# DEMO_NAME_LIBLINKS - Libraries to link
## Files that should be in the demo src dir
# DEMO_NAME.desktop - desktop shortcut for linux
# DEMO_NAME.png  - Icon used on Linux
# DEMO_NAME.rc  - AppInfo for windows
# DEMO_NAME.ico  - Icon used on Windows
# DEMO_NAME.icns - Icon used on Mac Os
macro(MAKE_DEMO)
    if(APPLE)
        set(PLATFORM_EX_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.icns)
        set_source_files_properties(${PLATFORM_EX_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    elseif(WIN32)
        set(PLATFORM_EX_SRC ${PROJECT_NAME}.rc)
    endif()

    add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${${PROJECT_NAME}_SRC} ${PLATFORM_EX_SRC})
    add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_DEPENDS})
    target_link_libraries ( ${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_LIBLINKS})

    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.ff7tk.${PROJECT_NAME}"
        MACOSX_BUNDLE_DISPLAY_NAME "${PROJECT_NAME}"
        MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME}"
        MACOSX_BUNDLE_DISPLAY_NAME "${PROJECT_NAME}"
        MACOSX_BUNDLE_INFO_STRING "${PROJECT_DESCRIPTION}"
        MACOSX_BUNDLE_COPYRIGHT "2012-2022 ff7tk Authors"
        MAXOSX_BUNDLE_ICON_FILE ${PROJECT_NAME}.icns
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    )
    if(APPLE)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${PLATFORMDEPLOYQT} $<TARGET_FILE:${PROJECT_NAME}> -qmldir=${CMAKE_CURRENT_SOURCE_DIR}
    )
    elseif(UNIX AND NOT APPLE)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            INSTALL_RPATH ${INSTALL_RPATH_STRING}
        )
        install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.desktop" DESTINATION share/applications/ COMPONENT ${PROJECT_NAME})
        install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.png" DESTINATION share/pixmaps COMPONENT ${PROJECT_NAME})
    endif()

    install(TARGETS ${PROJECT_NAME}
        COMPONENT ${PROJECT_NAME}
        BUNDLE DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    set_property(GLOBAL APPEND PROPERTY ff7tk_targets ${PROJECT_NAME})
    list(APPEND CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME};${PROJECT_NAME}")
endmacro()

if(WIDGET_GALLERY)
    add_subdirectory(ff7tkWidgetGallery)
endif()

if(QML_GALLERY)
    add_subdirectory(ff7tkQmlGallery)
endif()


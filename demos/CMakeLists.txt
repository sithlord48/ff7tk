set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

#ff7tk Demo Applications
option(WIDGET_GALLERY "Build the widget based gallery" ON)
option(QML_GALLERY "Build the qml based gallery" ON)

set(THIS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
#This Macro Creates a ff7tk demo from a project
#Then Sets all install and pacakge info
##REQUIREMENTS
# The INSTALL_RPATH_STRING has been set (main CMakeLists.txt)
# Caller is a project with NAME VERSION AND DESCRIPTION set
# DEMO_NAME_SRC - Source for the demo
# DEMO_NAME_DEPENDS - ff7tk items the demo depends on
# DEMO_NAME_LIBLINKS - Libraries to link
## Having these in the demo dir will override the generic versions
# DEMO_NAME.png  - Icon used on Linux
# DEMO_NAME.rc  - AppInfo for windows
# DEMO_NAME.ico  - Icon used on Windows
# DEMO_NAME.icns - Icon used on Mac Os
macro(MAKE_DEMO)
    if(APPLE)
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.icns)
            set(PLATFORM_EX_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.icns)
        else()
            configure_file(${THIS_DIR}/demoTemplate.icns ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.icns COPYONLY)
            set(PLATFORM_EX_SRC ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.icns)
        endif()
        set_source_files_properties(${PLATFORM_EX_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    elseif(WIN32)
        if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.ico)
            configure_file(${THIS_DIR}/demoTemplate.ico ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.ico COPYONLY)
        endif()
        configure_file(${THIS_DIR}/demoTemplate.rc.in ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc @ONLY)
        set(PLATFORM_EX_SRC ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc)
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
            COMMAND ${PLATFORMDEPLOYQT} $<TARGET_BUNDLE_DIR:${PROJECT_NAME}> -qmldir=${CMAKE_CURRENT_SOURCE_DIR}
        )
    elseif(UNIX AND NOT APPLE)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            INSTALL_RPATH ${INSTALL_RPATH_STRING}
        )
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.desktop)
            install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.desktop" DESTINATION ${CMAKE_INSTALL_DATADIR}/applications/ COMPONENT ${PROJECT_NAME})
        else()
            configure_file(${THIS_DIR}/demoTemplate.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.desktop @ONLY)
            install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.desktop" DESTINATION ${CMAKE_INSTALL_DATADIR}/applications/ COMPONENT ${PROJECT_NAME})
        endif()
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.png)
            install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.png" DESTINATION ${CMAKE_INSTALL_DATADIR}/pixmaps COMPONENT ${PROJECT_NAME})
        else()
            install(FILES "${THIS_DIR}/demoTemplate.png" DESTINATION ${CMAKE_INSTALL_DATADIR}/pixmaps RENAME "${PROJECT_NAME}.png" COMPONENT ${PROJECT_NAME})
        endif()
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


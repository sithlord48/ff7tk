# SPDX-FileCopyrightText: 2023 Chris Rizzitello <sithlord48@gmail.com>
# SPDX-License-Identifier: MIT

#Contains Various Macros to be included
#####~~~~~~~~~~~~~~~~~~~~~MAKE_LIBRARY~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#This makes a Library and sets up all the install rules
# Calls add_library or qt_add_qml_module based on the provided options
# LIB_TARGET NAME of Library to Make
# HEADER_INSTALL_DIR: Path to install headers
## The Follow should be by defined the caller before calling the macro
# LIB_TARGET_SRC
# LIB_TARGET_HEADERS
# LIB_TARGET_RESOURCES
# LIB_TARGET_PublicLIBLINKS
# LIB_TARGET_PrivateLIBLINKS
## QML PLUGINS##
# By Default a libary will be made if you would instead like a QML MODULE
# LIB_TARGET_MAKEQMLMODULE - If True A QML Module will be made by calling qt_add_qml_module instead of add_library
# LIB_TARGET_URI - The URI of the new module
# LIB_TARGET_RESOURCE_PREFIX - Set to /qt/qml unless otherwise specified
# LIB_TARGET_DEPENDS - The list of Qml Modules this module will depend upon. Depends are added to LIB_TARGET_PublicLIBLINKS
# LIB_TARGET_QML_FILES - QML Files that are part of the module

macro(MAKE_LIBRARY LIB_TARGET HEADER_INSTALL_DIR)
    if(DEFINED ${LIB_TARGET}_MAKEQMLMODULE)
        if(NOT DEFINED ${LIB_TARGET}_RESOURCE_PREFIX)
            set(RESOURCE_PREFIX "/qt/qml")
        endif()

        qt_add_qml_module(${LIB_TARGET}
            VERSION 1.0
            URI ${${LIB_TARGET}_URI}
            RESOURCE_PREFIX ${RESOURCE_PREFIX}
            DEPENDENCIES ${${LIB_TARGET}_DEPENDS}
            QML_FILES ${${LIB_TARGET}_QMLFILES}
            SOURCES ${${LIB_TARGET}_SRC} ${${LIB_TARGET}_HEADERS}
            NO_PLUGIN
        )
    else()
        add_library (${LIB_TARGET} SHARED
                ${${LIB_TARGET}_SRC}
                ${${LIB_TARGET}_HEADERS}
                ${${LIB_TARGET}_RESOURCES}
    )
    endif()
    add_library (ff7tk::${LIB_TARGET} ALIAS ${LIB_TARGET})

    #Embed rc file with Version info
    if(WIN32)
        set(LIB_NAME ${LIB_TARGET})
        configure_file(${CMAKE_SOURCE_DIR}/cmake/_template/libTemplate.rc.in ${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}.rc @ONLY)
        target_sources(${LIB_TARGET} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}.rc)
    endif()

    #Generate the non .h ending header let the user include "HEADER" or "HEADER.h"
    foreach ( HEADER ${${LIB_TARGET}_HEADERS})
        if(${HEADER} MATCHES "^/" OR ${HEADER} MATCHES "^[A-Za-z]:")
            string(FIND ${HEADER} "/" lastSlash REVERSE)
            string(SUBSTRING ${HEADER} 0 ${lastSlash} RMSTRING)
            string(REPLACE "${RMSTRING}/" "" HEADER ${HEADER})
        endif()
        set(fileContent "#pragma once\n#include<${HEADER}>\n")
        string(REPLACE ".h" "" HEADER ${HEADER})
        file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${HEADER} ${fileContent})
        list(APPEND ALIASHEADERS ${CMAKE_CURRENT_BINARY_DIR}/${HEADER})
    endforeach()

    if(APPLE)
        if(${BUILD_FRAMEWORKS})
            target_include_directories(${LIB_TARGET} PUBLIC  $<BUILD_INTERFACE:$<TARGET_BUNDLE_CONTENT_DIR:${LIB_TARGET}>/Headers>)
        else()
            set_target_properties(${LIB_TARGET} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
        endif()
    endif()

    if(UNIX AND NOT ${BUILD_FRAMEWORKS})
        set_target_properties(${LIB_TARGET} PROPERTIES INSTALL_RPATH ${INSTALL_RPATH_STRING})
    endif()

    set_target_properties(${LIB_TARGET} PROPERTIES
        FRAMEWORK ${BUILD_FRAMEWORKS}
        FRAMEWORK_VERSION ${PROJECT_VERSION_MAJOR}
        MACOSX_FRAMEWORK_IDENTIFIER com.sithlord48.${LIB_TARGET}
        VERSION "${PROJECT_VERSION}"
        SOVERSION "${PROJECT_VERSION_MAJOR}"
        PUBLIC_HEADER "${${LIB_TARGET}_HEADERS}"
        MAP_IMPORTED_CONFIG_DEBUG RELWITHDEBINFO
        MAP_IMPORTED_CONFIG_RELEASE RELWITHDEBINFO
        MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELWITHDEBINFO
        MAP_IMPORTED_CONFIG_MINSIZEREL RELWITHDEBINFO
    )

    target_include_directories(${LIB_TARGET} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include/${HEADER_INSTALL_DIR}>
    )

    target_link_libraries (${LIB_TARGET}
        PUBLIC
          ${${LIB_TARGET}_PublicLIBLINKS}
        PRIVATE
          ${${LIB_TARGET}_PrivateLIBLINKS}
        )

    generate_export_header(${LIB_TARGET})
    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )
    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_TARGET}Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}Config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
    )
    install(TARGETS ${LIB_TARGET}
        EXPORT ff7tkTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT ff7tk_libraries
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT ff7tk_libraries
            NAMELINK_COMPONENT ff7tk_headers
        FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT ff7tk_libraries
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT ff7tk_headers
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${HEADER_INSTALL_DIR}
            COMPONENT ff7tk_headers
    )
    install (FILES ${ALIASHEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${HEADER_INSTALL_DIR}
        COMPONENT ff7tk_headers
    )

    if(UNIX)
        if(NOT APPLE)
            add_custom_command(TARGET ${LIB_TARGET} POST_BUILD
                COMMAND ${CMAKE_OBJCOPY} --only-keep-debug $<TARGET_FILE:${LIB_TARGET}> $<TARGET_FILE:${LIB_TARGET}>.dbg
                COMMAND ${CMAKE_STRIP} --strip-debug $<TARGET_FILE:${LIB_TARGET}>
                COMMAND ${CMAKE_OBJCOPY} --add-gnu-debuglink=$<TARGET_FILE:${LIB_TARGET}>.dbg $<TARGET_FILE:${LIB_TARGET}>
            )
        else()
            add_custom_command(TARGET ${LIB_TARGET} POST_BUILD
                COMMAND dsymutil -f $<TARGET_FILE:${LIB_TARGET}> -o $<TARGET_FILE:${LIB_TARGET}>.dbg
            )
        endif()
        install(FILES $<TARGET_FILE:${LIB_TARGET}>.dbg
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/debug
            COMPONENT ff7tk_debug
        )
    elseif(WIN32)
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_BASE_NAME:${LIB_TARGET}>.pdb
            DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT ff7tk_debug
        )
    endif()

    install(
        EXPORT ff7tkTargets
        NAMESPACE ff7tk::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
        COMPONENT ff7tk_headers
    )

    install(
        FILES
          ${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}Config.cmake
          ${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
        COMPONENT ff7tk_headers
    )

    export(EXPORT ff7tkTargets FILE ${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}Targets.cmake)
    set_property(GLOBAL APPEND PROPERTY ff7tk_targets ${LIB_TARGET})

    sbom_add(TARGET ${LIB_TARGET})

endmacro()

#####~~~~~~~~~~~~~~~~~~~~~MAKE_DEMO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
            configure_file(${CMAKE_SOURCE_DIR}/cmake/_template/demoTemplate.icns ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.icns COPYONLY)
            set(PLATFORM_EX_SRC ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.icns)
        endif()
        set_source_files_properties(${PLATFORM_EX_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    elseif(WIN32)
        if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.ico)
            configure_file(${CMAKE_SOURCE_DIR}/cmake/_template/demoTemplate.ico ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.ico COPYONLY)
        endif()
        configure_file(${CMAKE_SOURCE_DIR}/cmake/_template/demoTemplate.rc.in ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc @ONLY)
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
        MACOSX_BUNDLE_COPYRIGHT "2012-2023 ff7tk Authors"
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
            configure_file(${CMAKE_SOURCE_DIR}/cmake/_template/demoTemplate.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.desktop @ONLY)
            install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.desktop" DESTINATION ${CMAKE_INSTALL_DATADIR}/applications/ COMPONENT ${PROJECT_NAME})
        endif()
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.png)
            install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.png" DESTINATION ${CMAKE_INSTALL_DATADIR}/pixmaps COMPONENT ${PROJECT_NAME})
        else()
            install(FILES "${CMAKE_SOURCE_DIR}/cmake/_template/demoTemplate.png" DESTINATION ${CMAKE_INSTALL_DATADIR}/pixmaps RENAME "${PROJECT_NAME}.png" COMPONENT ${PROJECT_NAME})
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
#####~~~~~~~~~~~~~~~~~~~~~MAKE_TEST~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# MAKE_TEST - Set up a unit test
# NAME - Name of the new Test
# FILE - cpp File for the Test
macro (MAKE_TEST NAME FILE)
    get_filename_component(curDir ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    set(DEP_LIB ff7tk)
    if( NOT ${curDir} MATCHES core)
        string(SUBSTRING ${curDir} 0 1 FIRST_LETTER)
        string(TOUPPER ${FIRST_LETTER} FIRST_LETTER)
        string(REGEX REPLACE "^.(.*)" "${FIRST_LETTER}\\1" curDir_UPPER "${curDir}")
        string(APPEND DEP_LIB "${curDir_UPPER}")
    endif()
    add_executable( ${NAME} ${FILE} )
    target_link_libraries( ${NAME} ${DEP_LIB} Qt::Test)
    add_test(NAME ${NAME} COMMAND $<TARGET_FILE:${NAME}> WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../src/${curDir}")
    set_tests_properties(${NAME} PROPERTIES DEPENDS ${DEP_LIB})
    set_property(GLOBAL APPEND PROPERTY ff7tk_tests ${NAME})
endmacro()

option(DATA "Build the data libary" ON)
option(FORMATS "Build the formats libary" ON)
option(UTILS "Build utility library (Requires zlib)" ON)
option(WIDGETS "Build the widget libary" ON)
option(FRAMEWORKS "Build Frameworks on MacOS (EXPERMANTAL)" OFF)

if(FRAMEWORKS AND APPLE)
    set(BUILD_FRAMEWORKS TRUE)
else()
    set(BUILD_FRAMEWORKS FALSE)
endif()
#Refer to this directory
set(THIS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
#This makes a Library and sets up all the install rules
# LIB_TARGET NAME of Library to Make
# HEADER_INSTALL_DIR: Path to install headers
## The Follow should be by defined the caller before calling the macro
# LIB_TARGET_SRC
# LIB_TARGET_HEADERS
# LIB_TARGET_RESOURCES
# LIB_TARGET_PublicLIBLINKS
# LIB_TARGET_PrivateLIBLINKS
macro(MAKE_LIBRARY LIB_TARGET HEADER_INSTALL_DIR)

    add_library (${LIB_TARGET} SHARED
            ${${LIB_TARGET}_SRC}
            ${${LIB_TARGET}_HEADERS}
            ${${LIB_TARGET}_RESOURCES}
    )
    add_library (ff7tk::${LIB_TARGET} ALIAS ${LIB_TARGET})

    #Embed rc file with Version info
    if(WIN32)
        set(LIB_NAME ${LIB_TARGET})
        configure_file(${THIS_DIR}/libTemplate.rc.in ${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}.rc @ONLY)
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
        set_target_properties(${LIB_TARGET} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
        if(${BUILD_FRAMEWORKS})
            target_include_directories(${LIB_TARGET} PUBLIC  $<BUILD_INTERFACE:$<TARGET_BUNDLE_CONTENT_DIR:${LIB_TARGET}>/Headers>)
        endif()
    endif()

    if(UNIX)
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
        COMPATIBILITY SameMinorVersion
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
endmacro()

add_subdirectory(core)
if(DATA)
    add_subdirectory(data)
endif()
if(WIDGETS)
    add_subdirectory(widgets)
endif()

if(UTILS)
    add_subdirectory(utils)
endif()

if(FORMATS)
    add_subdirectory(formats)
endif()

install(
    EXPORT
        ff7tkTargets
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
    FILE
        ff7tkTargets.cmake
    NAMESPACE
        ff7tk::
    COMPONENT ff7tk_headers
)

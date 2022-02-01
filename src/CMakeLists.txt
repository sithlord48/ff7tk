option(FORMATS "Build the formats libary" ON)
option(UTILS "Build utility library (Requires zlib)" ON)
option(WIDGETS "Build the widget libary" ON)
option(FRAMEWORKS "Build Frameworks on MacOS (EXPERMANTAL)" OFF)

if(FRAMEWORKS AND APPLE)
    set(BUILD_FRAMEWORKS TRUE)
else()
    set(BUILD_FRAMEWORKS FALSE)
endif()

macro(INSTALL_LIBRARY LIB_TARGET HEADER_INSTALL_DIR)
    generate_export_header(${LIB_TARGET})
    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )
    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_TARGET}Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}Config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
    )
    install(TARGETS ${LIB_TARGET}
        EXPORT ff7tkTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT ff7tk_runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT ff7tk_runtime
            NAMELINK_COMPONENT ff7tk_development
        FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT ff7tk_runtime
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT ff7tk_development
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${HEADER_INSTALL_DIR}
            COMPONENT ff7tk_development
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
            COMPONENT ff7tk_development
        )
    elseif(WIN32)
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_BASE_NAME:${LIB_TARGET}>.pdb
            DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT ff7tk_development
        )
    endif()

    install(
        EXPORT ff7tkTargets
        NAMESPACE ff7tk::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
        COMPONENT ff7tk_development
    )

    install(
        FILES
          ${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}Config.cmake
          ${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
        COMPONENT ff7tk_development
    )

    export(EXPORT ff7tkTargets FILE ${CMAKE_CURRENT_BINARY_DIR}/${LIB_TARGET}Targets.cmake)
    set_property(GLOBAL APPEND PROPERTY ff7tk_targets ${LIB_TARGET})
endmacro()

add_subdirectory(data)

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
    COMPONENT ff7tk_development
)

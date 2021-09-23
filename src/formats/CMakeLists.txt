find_package(QT NAMES Qt6 Qt5 COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED NO_MODULE COMPONENTS
    Core
)

set(UTILS ON CACHE BOOL "Build ff7tkUtils Lib" FORCE)
find_library(ff7tkUtils ${CMAKE_BINARY_DIR}/src/utils)

set ( ff7tkFormats_SRC
        Archive.cpp
        IsoArchive.cpp
        Lgp_p.cpp
        Lgp.cpp
)

set ( ff7tkFormats_HEADERS
        Archive.h
        IsoArchive.h
        Lgp_p.h
        Lgp.h
        ${CMAKE_CURRENT_BINARY_DIR}/ff7tkformats_export.h
)

add_library (ff7tkFormats
  SHARED
    ${ff7tkFormats_SRC}
    ${ff7tkFormats_HEADERS}
)
add_library(ff7tk::ff7tkFormats ALIAS ff7tkFormats)

if(APPLE)
    set_target_properties(ff7tkFormats PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "@loader_path/../Frameworks @loader_path @executable_path @executable_path/../Frameworks"
    )
    if(${BUILD_FRAMEWORKS})
        target_include_directories(ff7tkFormats PUBLIC  $<BUILD_INTERFACE:$<TARGET_BUNDLE_CONTENT_DIR:ff7tkFormats>/Headers>)
    endif()
endif()

set_target_properties(ff7tkFormats PROPERTIES
    FRAMEWORK ${BUILD_FRAMEWORKS}
    FRAMEWORK_VERSION ${PROJECT_VERSION_MAJOR}
    MACOSX_FRAMEWORK_IDENTIFIER com.sithlord48.ff7tkFormats
    ff7tkFormats PROPERTIES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    PUBLIC_HEADER "${ff7tkFormats_HEADERS}"
)

target_include_directories(ff7tkFormats
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include/ff7tk/formats>
)

target_link_libraries (ff7tkFormats PUBLIC
        Qt::Core
        ff7tk::ff7tkUtils
)

generate_export_header(ff7tkFormats BASE_NAME ff7tkformats)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkFormatsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/ff7tkFormatsConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkFormatsConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
)

install(TARGETS ff7tkFormats
    EXPORT ff7tkTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT ff7tk_RUNTIME
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT ff7tk_RUNTIME
        NAMELINK_COMPONENT ff7tk_DEVELOPMENT
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT ff7tk_RUNTIME
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT ff7tk_DEVELOPMENT
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/formats
        COMPONENT ff7tk_DEVELOPMENT
)

install(
    EXPORT ff7tkTargets
    COMPONENT ff7tkFormats
    NAMESPACE ff7tk::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
)

install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/ff7tkFormatsConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/ff7tkFormatsConfigVersion.cmake
    COMPONENT ff7tkFormats
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
)
export(EXPORT ff7tkTargets FILE ${CMAKE_CURRENT_BINARY_DIR}/ff7tkTargets.cmake)

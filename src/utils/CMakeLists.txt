find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
    Gui
)
find_package( ZLIB REQUIRED)

set ( ff7tkUtils_SRC
        GZIP.cpp #NEEDS ZLIB
        GZIPPS.cpp
        LZS.cpp
        PsColor.cpp
        QLockedFile.cpp
    )

    set ( ff7tkUtils_HEADERS
        GZIP.h #NEEDS ZLIB
        GZIPPS.h
        LZS.h
        PsColor.h
        QLockedFile.h
    )

add_library (ff7tkUtils SHARED ${ff7tkUtils_SRC} ff7tkutils_export.h)
add_library(ff7tk::ff7tkUtils ALIAS ff7tkUtils)

target_include_directories(ff7tkUtils
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/ff7tk/utils>
  INTERFACE
    $<INSTALL_INTERFACE:include/ff7tk/utils>
)

target_link_libraries (ff7tkUtils PUBLIC
        Qt5::Core
        Qt5::Gui
        ZLIB::ZLIB
 )

 set_target_properties(
    ff7tkUtils PROPERTIES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    PUBLIC_HEADER "${ff7tkUtils_HEADERS}"
)

generate_export_header(ff7tkUtils BASE_NAME ff7tkutils)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkUtilsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/ff7tkUtilsConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkUtilsConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
)

include(GNUInstallDirs)

install(TARGETS ff7tkUtils
    EXPORT ff7tkTargets
    COMPONENT ff7tkUtils
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/utils
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/ff7tkutils_export.h
    COMPONENT ff7tkUtils
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/utils
)

install(
    EXPORT ff7tkTargets
    NAMESPACE ff7tk::
    COMPONENT ff7tkUtils
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
)

install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/ff7tkUtilsConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/ff7tkUtilsConfigVersion.cmake
    COMPONENT ff7tkUtils
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
)
export(EXPORT ff7tkTargets FILE ${CMAKE_CURRENT_BINARY_DIR}/ff7tkTargets.cmake)

find_package(Qt${QT_DEFAULT_MAJOR_VERSION} REQUIRED NO_MODULE COMPONENTS
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
        ${CMAKE_CURRENT_BINARY_DIR}/ff7tkutils_export.h
)

add_library (ff7tkUtils
  SHARED
    ${ff7tkUtils_SRC}
    ${ff7tkUtils_HEADERS}
)
add_library(ff7tk::ff7tkUtils ALIAS ff7tkUtils)

if(APPLE)
    set_target_properties(ff7tkUtils PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "@loader_path/../Frameworks @loader_path @executable_path @executable_path/../Frameworks"
    )
    if(${BUILD_FRAMEWORKS})
        target_include_directories(ff7tkUtils PUBLIC $<BUILD_INTERFACE:$<TARGET_BUNDLE_CONTENT_DIR:ff7tkUtils>/Headers>)
    endif()
endif()

set_target_properties(ff7tkUtils PROPERTIES
    FRAMEWORK ${BUILD_FRAMEWORKS}
    FRAMEWORK_VERSION ${PROJECT_VERSION_MAJOR}
    MACOSX_FRAMEWORK_IDENTIFIER com.sithlord48.ff7tkUtils
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    PUBLIC_HEADER "${ff7tkUtils_HEADERS}"
)

target_include_directories(ff7tkUtils PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include/ff7tk/utils>
)

target_link_libraries (ff7tkUtils PUBLIC
    Qt::Core
    Qt::Gui
    ZLIB::ZLIB
 )

generate_export_header(ff7tkUtils BASE_NAME ff7tkutils)

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

install(TARGETS ff7tkUtils
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
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/utils
        COMPONENT ff7tk_DEVELOPMENT
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

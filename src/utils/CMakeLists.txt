find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
    Gui
)
include_directories(../src)
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

target_include_directories(ff7tkUtils PRIVATE ${PROJECT_BINARY_DIR/src/data})
target_include_directories(ff7tkUtils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
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
include(GNUInstallDirs)

install(TARGETS ff7tkUtils
    EXPORT ff7tkUtilsConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/widgets
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ff7tkutils_export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/utils)

install(EXPORT ff7tkUtilsConfig NAMESPACE ff7tk:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk)
export(TARGETS ff7tkUtils FILE ff7tkUtils.cmake)

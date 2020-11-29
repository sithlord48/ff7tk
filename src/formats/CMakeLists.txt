find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
)

set(UTILS ON CACHE BOOL "Build ff7tkUtils Lib" FORCE)

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
    )
add_library (ff7tkFormats SHARED ${ff7tkFormats_SRC} ff7tkformats_export.h)
add_library(ff7tk::ff7tkFormats ALIAS ff7tkFormats)

target_include_directories(ff7tkFormats PRIVATE ${PROJECT_BINARY_DIR}/src/utils)
target_include_directories(ff7tkFormats PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:/include/ff7tk/formats>
)

target_link_libraries (ff7tkFormats PUBLIC
        Qt5::Core
    )
target_link_libraries (ff7tkFormats PRIVATE ff7tk::ff7tkUtils)

set_target_properties(
    ff7tkFormats PROPERTIES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    PUBLIC_HEADER "${ff7tkFormats_HEADERS}"
)

generate_export_header(ff7tkFormats BASE_NAME ff7tkformats)
include(GNUInstallDirs)

install(TARGETS ff7tkFormats
    EXPORT ff7tkFormatsConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/formats
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ff7tkformats_export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/formats)

install(EXPORT ff7tkFormatsConfig NAMESPACE ff7tk:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk)
export(TARGETS ff7tkFormats FILE ff7tkFormats.cmake)

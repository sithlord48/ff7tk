find_package(Qt${QT_DEFAULT_MAJOR_VERSION} REQUIRED NO_MODULE COMPONENTS
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
    set_target_properties(ff7tkFormats PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
    if(${BUILD_FRAMEWORKS})
        target_include_directories(ff7tkFormats PUBLIC  $<BUILD_INTERFACE:$<TARGET_BUNDLE_CONTENT_DIR:ff7tkFormats>/Headers>)
    endif()
endif()

if(UNIX)
    set_target_properties(ff7tkFormats PROPERTIES INSTALL_RPATH ${INSTALL_RPATH_STRING})
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

INSTALL_LIBRARY(ff7tkFormats ff7tk/formats)

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
    set_target_properties(ff7tkUtils PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
    if(${BUILD_FRAMEWORKS})
        target_include_directories(ff7tkUtils PUBLIC $<BUILD_INTERFACE:$<TARGET_BUNDLE_CONTENT_DIR:ff7tkUtils>/Headers>)
    endif()
endif()

if(UNIX)
    set_target_properties(ff7tkUtils PROPERTIES INSTALL_RPATH ${INSTALL_RPATH_STRING})
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

INSTALL_LIBRARY(ff7tkUtils ff7tk/utils)

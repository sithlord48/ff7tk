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

add_library (ff7tkUtils SHARED ${ff7tkUtils_SRC})
add_library(ff7tk::ff7tkUtils ALIAS ff7tkUtils)

target_link_libraries (ff7tkUtils PUBLIC
        Qt5::Core
        Qt5::Gui
        ZLIB::ZLIB
 )
generate_export_header(ff7tkUtils BASE_NAME ff7tkutils)
include(GNUInstallDirs)

install(TARGETS ff7tkUtils
    EXPORT ff7tkUtilsConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install (
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk
    FILES_MATCHING PATTERN "*.h"
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkutils_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/utils
)

install(EXPORT ff7tkUtilsConfig NAMESPACE ff7tk:: DESTINATION share/ff7tk/cmake)
export(TARGETS ff7tkUtils FILE ff7tkUtils.cmake)

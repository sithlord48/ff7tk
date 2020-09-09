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
add_library (ff7tkFormats SHARED ${ff7tkFormats_SRC})
add_library(ff7tk::ff7tkFormats ALIAS ff7tkFormats)
target_include_directories(ff7tkFormats PRIVATE ${PROJECT_BINARY_DIR}/src/utils)

target_link_libraries (ff7tkFormats PUBLIC
        Qt5::Core
        ff7tk::ff7tkUtils
    )
generate_export_header(ff7tkFormats BASE_NAME ff7tkformats)

include(GNUInstallDirs)

install(TARGETS ff7tkFormats
    EXPORT ff7tkFormatsConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install (
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk
    FILES_MATCHING PATTERN "*.h"
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkformats_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/formats
)

install(EXPORT ff7tkFormatsConfig NAMESPACE ff7tk:: DESTINATION share/ff7tk/cmake)
export(TARGETS ff7tkFormats FILE ff7tkFormats.cmake)

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

set(ff7tkFormats_PublicLIBLINKS
      Qt::Core
      ff7tk::ff7tkUtils
)
MAKE_LIBRARY(ff7tkFormats ff7tk/formats)

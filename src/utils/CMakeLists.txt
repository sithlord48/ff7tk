find_package(Qt6 REQUIRED NO_MODULE COMPONENTS
    Core
    Gui
)

find_package( ZLIB REQUIRED)

set(ff7tkUtils_SRC
    IO.cpp
    GZIP.cpp #NEEDS ZLIB
    GZIPPS.cpp
    LZS.cpp
    PsColor.cpp
    QLockedFile.cpp
)

set(ff7tkUtils_HEADERS
    IO.h
    GZIP.h #NEEDS ZLIB
    GZIPPS.h
    LZS.h
    PsColor.h
    QLockedFile.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkutils_export.h
)

set(ff7tkUtils_PublicLIBLINKS
    Qt::Core
    Qt::Gui
    ZLIB::ZLIB
)

MAKE_LIBRARY(ff7tkUtils ff7tk/utils)

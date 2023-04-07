find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
    Gui
)

set(UTILS ON CACHE BOOL "Build ff7tkUtils Lib" FORCE)
find_library(ff7tkUtils ${CMAKE_BINARY_DIR}/src/utils)

set(ff7tkFormats_SRC
    Akao.cpp
    AkaoIO.cpp
    Archive.cpp
    IsoArchive.cpp
    IsoArchiveFF7.cpp
    Lgp_p.cpp
    Lgp.cpp
    TblFile.cpp
    TexFile.cpp
    TextureFile.cpp
    TimFile.cpp
    WindowBinFile.cpp
)

set(ff7tkFormats_HEADERS
    Akao.h
    AkaoIO.h
    Archive.h
    IsoArchive.h
    IsoArchiveFF7.h
    Lgp_p.h
    Lgp.h
    TblFile.h
    TexFile.h
    TextureFile.h
    TimFile.h
    WindowBinFile.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkformats_export.h
)

set(ff7tkFormats_PublicLIBLINKS
      Qt::Core
      Qt::Gui
      ff7tk::ff7tkUtils
)

MAKE_LIBRARY(ff7tkFormats ff7tk/formats)

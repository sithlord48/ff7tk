# SPDX-FileCopyrightText: Chris Rizzitello <sithlord48@gmail.com>
# SPDX-License-Identifier: CC0-1.0

find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
    Gui
)

find_package( ZLIB REQUIRED)
sbom_add(PACKAGE ZLIB VERSION ${ZLIB_VERSION})

if(ZLIB_FOUND)
    define_property(GLOBAL PROPERTY zlib_target BRIEF_DOCS "zlib dll path" FULL_DOCS "zlib.dll path")
    if(EXISTS ${ZLIB_ROOT}/bin/zlib.dll)
        set_property(GLOBAL APPEND PROPERTY zlib_target "${ZLIB_ROOT}/bin/zlib.dll")
    elseif(EXISTS ${ZLIB_ROOT}/bin/zlib1.dll)
        set_property(GLOBAL APPEND PROPERTY zlib_target "${ZLIB_ROOT}/bin/zlib1.dll")
    elseif(EXISTS ${ZLIB_ROOT}/bin/libzlib.dll)
        set_property(GLOBAL APPEND PROPERTY zlib_target "${ZLIB_ROOT}/bin/libzlib.dll")
    elseif(EXISTS ${ZLIB_ROOT}/bin/libzlib1.dll)
        set_property(GLOBAL APPEND PROPERTY zlib_target "${ZLIB_ROOT}/bin/libzlib1.dll")
    endif()
endif()

set(ff7tkUtils_SRC
    IO.cpp
    GZIP.cpp #NEEDS ZLIB
    GZIPPS.cpp
    LZS.cpp
    PsColor.cpp
    PsfFile.cpp
    QLockedFile.cpp
)

set(ff7tkUtils_HEADERS
    IO.h
    GZIP.h #NEEDS ZLIB
    GZIPPS.h
    LZS.h
    PsColor.h
    PsfFile.h
    QLockedFile.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkutils_export.h
)

set(ff7tkUtils_PublicLIBLINKS
    Qt::Core
    Qt::Gui
    ZLIB::ZLIB
)

MAKE_LIBRARY(ff7tkUtils ff7tk/utils)

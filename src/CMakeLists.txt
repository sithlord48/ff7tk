# SPDX-FileCopyrightText: Chris Rizzitello <sithlord48@gmail.com>
# SPDX-License-Identifier: MIT

option(DATA "Build the data libary" ON)
option(FORMATS "Build the formats libary" ON)
option(UTILS "Build utility library (Requires zlib)" ON)
option(QUICK "Build ff7tkQuick libraries" ON)
option(WIDGETS "Build the widget libary" ON)

if(FRAMEWORKS AND APPLE)
    set(BUILD_FRAMEWORKS TRUE)
else()
    set(BUILD_FRAMEWORKS FALSE)
endif()

add_subdirectory(ff7tk)

if(DATA)
    add_subdirectory(data)
endif()
if(WIDGETS)
    add_subdirectory(widgets)
endif()

if(UTILS)
    add_subdirectory(utils)
endif()

if(FORMATS)
    add_subdirectory(formats)
endif()

if(QUICK)
    add_subdirectory(ff7tkQuick)
endif()

install(
    EXPORT
        ff7tkTargets
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
    FILE
        ff7tkTargets.cmake
    NAMESPACE
        ff7tk::
    COMPONENT ff7tk_headers
)

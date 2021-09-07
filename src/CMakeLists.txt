
option(FORMATS "Build the formats libary" ON)
option(UTILS "Build utility library (Requires zlib)" ON)
option(WIDGETS "Build the widget libary" ON)

add_subdirectory(data)

if (APPLE)
  set(CMAKE_MACOSX_RPATH ON)
  set(CMAKE_INSTALL_NAME_DIR @executable_path)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
else()
  set(CMAKE_INSTALL_RPATH $ORIGIN)
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

install(
    EXPORT
        ff7tkTargets
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
    FILE
        ff7tkTargets.cmake
    NAMESPACE
        ff7tk::
)
